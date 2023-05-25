#include "Renderer.h"
#include "Application.h"
#include "Model.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "ResourceManager.h"
#include "DrawLine.h"
#include "Light.h"
#include "Skybox.h"
#include "Component.h"
#include "Log.h"
#include "Behaviour.h"
#include "AudioSource.h"
#include <iostream>
#include "Animation.h"
#include "Animator.h"
#include "RigidBody.h"
#include "SceneSaver.h"
#include "WorldPhysics.h"
#include "ScriptInterpreter.h"
#include "UIImage.h"
#include "IMGUI/imgui.h"

using namespace GigRenderer;

Application::Application()
{
    Init();

    WorldPhysics::GetInstance().InitPhysicWorld();
    Scene::GetInstance().LoadScene(Scene::GetInstance().GetCurrentSceneName());
    sk = GameObjectManager::CreateGameObject("sk");
    sk->SetModel("Engine/Models/Monke.fbx");
    sk->SetTexture("Engine/Textures/Monkey.png");
    Animation* anim = new Animation("Engine/Animations/Idle.fbx", sk->GetModel());
    Animation* animRun = new Animation("Engine/Animations/Run.fbx", sk->GetModel());
    sk->GetTransform().SetWorldScale(0.005f);
    sk->AddComponent<Animator>();
    sk->GetAnimator()->GetAnimationStateRoot().stateAnim = anim;
    sk->GetAnimator()->AddState( animRun, "Run", "Idle", 0.6f);
    sk->GetAnimator()->AddState(animRun, "Run2", "Idle", 0.5f);
    sk->GetAnimator()->AddState(anim, "Idle2", "Run2", 1);
}

Application::~Application()
{
    Lines::Clear();
    GameObjectManager::Cleanup();
    AudioSource::Clear();
    WorldPhysics::GetInstance().DestroyPhysicWorld();
}

Window& Application::GetWindow()
{
    return window;
}

EditorCamera& Application::GetEditorCamera()
{
    return editorCamera;
}

ShaderProgram& Application::GetMainShader()
{
    return mainShader;
}

lm::FMat4& Application::GetViewProj()
{
    return viewProj;
}

lm::FVec3& Application::GetViewPos()
{
    return viewPos;
}

void Application::Play()
{
    if (isEditor)
    {
        SCRIPT_INTERPRETER.RefreshBehaviours();
        StartGame();
        isEditor = false;
    }
    else
    {
        Stop();
    }
}

void Application::Pause()
{
    isPause = !isPause;
    for (int i = 0; i < GameObjectManager::GetSize(); i++)
    {
        GameObject* object = GameObjectManager::GetGameObject(i);
        if (object->IsActive())
        {
            if (AudioSource* audio = object->GetComponent<AudioSource>())
            {
                if (isPause)
                    audio->Pause();
                else
                    audio->UnPause();
            }
        }
    }
}

void Application::Stop()
{
    isPause = false;
    GameObjectManager::SetCurrentCamera(nullptr);
    Scene::GetInstance().ReloadScene(Scene::GetInstance().GetCurrentSceneName());
    isEditor = true;
}

void Application::ShowUI()
{
    showUI = !showUI;
}

void Application::UseEditorCam()
{
    useEditorCam = !useEditorCam;
}

bool Application::IsInEditor()
{
    return isEditor;
}
bool Application::IsInPause()
{
    return isPause;
}
bool Application::IsUsingEditorCam()
{
    return useEditorCam;
}
bool Application::IsShowUI()
{
    return showUI;
}
void Application::StartGame()
{
    for (int i = 0; i < GameObjectManager::GetSize(); i++)
    {
        const GameObject* object = GameObjectManager::GetGameObject(i);

        if (object->IsActive())
        {
            for (int j = 0; j < object->GetComponentCount(); j++)
                object->GetComponentByID(j)->Start();
        }
    }
}

void Application::Run()
{
    window.ProcessInput();
    Time::UpdateDeltaTime();
    Draw();

    if (!isEditor && !isPause)
        WorldPhysics::GetInstance().UpdatePhysics(Time::GetDeltaTime());

    WorldPhysics::GetInstance().DrawDebug();
}

void Application::SwapFrames()
{
    window.swapBuffers();
}

//ok

void Application::Init()
{
    window.Init();
    editorCamera.SetRatio(window.GetViewPortRatio());
    RENDERER.Init();
    Lines::Init();
    UIManager::Init();
    InitMainShader();

    //to remove
    UIManager::AddTextElement();
    UIManager::AddImageElement();
}

void Application::InitMainShader()
{
    auto* mainVertex = ResourceManager::Get<VertexShader>("Engine/Shaders/core_vert.vert");
    auto* mainFragment = ResourceManager::Get<FragmentShader>("Engine/Shaders/core_frag.frag");

    if (!mainShader.Link(mainVertex, mainFragment))
        std::cout << "Error linking main shader" << std::endl;

    ModelLocation = mainShader.GetUniform("model");
    viewProjLocation = mainShader.GetUniform("viewProj");
    viewPosLocation = mainShader.GetUniform("viewPos");

    nbLightLocation = mainShader.GetUniform("nbLights");
}

void Application::Draw()
{
    //ImGui::ShowDemoWindow();
    //ImGui::Text(sk->GetAnimator()->GetCurrentState()->stateName.c_str());
    //if (ImGui::Button("Idle"))
    //    sk->GetAnimator()->StateChange("Idle");

    //if (ImGui::Button("Run"))
    //    sk->GetAnimator()->StateChange("Run");

    //if (ImGui::Button("Run2"))
    //    sk->GetAnimator()->StateChange("Run2");

    //if (ImGui::Button("Idle2"))
    //    sk->GetAnimator()->StateChange("Idle2");
    ClearWindow();

    RENDERER.Disable(RD_DEPTH_TEST);
    if (GameObjectManager::GetSkyBox())
        GameObjectManager::GetSkyBox()->Draw();

    if (isEditor || useEditorCam)
    {
        editorCamera.Update();
    }
    //
    mainShader.Use(); //start using the main shader

    if (!isEditor && !isPause)
    {
        UpdateGameObjectComponent(); //first because components can change the transform, destroy etc
    }

    UpdateUniforms(); //then send the global uniforms
    UpdateLights(); //send the lights to the shader (lights are gameobject, so they have been updated)

    RENDERER.Enable(RD_DEPTH_TEST);
    RENDERER.DepthFunction(RD_LESS);
    UpdateGameObjectRender(); //render model if they have one

    mainShader.UnUse(); //stop using the main shader

    //update audio with camera position
    Camera* currentCamera = useEditorCam ? &editorCamera : GameObjectManager::GetCurrentCamera();
    AudioSource::UpdateAudioEngine(currentCamera);

    Lines::DrawLines(); //render debug lines or guizmos

    if (showUI)
        UIManager::DrawUI(); // render UI
}

void Application::ClearWindow()
{
    RENDERER.ClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    RENDERER.Clear(RD_COLOR_BUFFER_BIT | RD_DEPTH_BUFFER_BIT);
}

void Application::UpdateGameObjectComponent()
{
    for (int i = 0; i < GameObjectManager::GetSize(); i++)
    {
        const GameObject* object = GameObjectManager::GetGameObject(i);
        object->UpdateComponents();
    }

    for (int i = 0; i < GameObjectManager::GetSize(); i++)
    {
        const GameObject* object = GameObjectManager::GetGameObject(i);
        object->LateUpdate();
    }
}

void Application::UpdateGameObjectRender() const
{
    for (int i = 0; i < GameObjectManager::GetSize(); i++)
    {
        GameObject* object = GameObjectManager::GetGameObject(i);

        object->UpdateHierarchy();

        RENDERER.SetUniformValue(ModelLocation, UniformType::MAT4, &object->GetTransform().MatrixGetter());
        object->UpdateRender();
    }
}

void Application::UpdateLights() const
{
    int nbLight = GameObjectManager::GetDirLightSize();
    nbLight += GameObjectManager::GetPointLightSize();
    nbLight += GameObjectManager::GetSpotLightSize();

    RENDERER.SetUniformValue(nbLightLocation, UniformType::INT, &nbLight);

    GameObjectManager::SendLightsToShader();
}

void Application::UpdateUniforms() const
{
    Camera* cam = nullptr;
    if (isEditor || useEditorCam)
    {
        cam = &editorCamera;
    }
    else
    {
        if (GameObjectManager::GetCurrentCamera())
        {
            if (GameObjectManager::GetCurrentCamera()->IsActive())
            {
                cam = GameObjectManager::GetCurrentCamera();
            }
        }
    }

    if (cam)
    {
        viewProj = cam->GetProjectionMatrix() * cam->CreateViewMatrix();
        viewPos = cam->GetTransform().GetWorldPosition();
    }
    else
    {
        viewProj = lm::FMat4(0);
        viewPos = lm::FVec3(0);
    }

    RENDERER.SetUniformValue(viewProjLocation, UniformType::MAT4, &viewProj);
    RENDERER.SetUniformValue(viewPosLocation, UniformType::VEC3, &viewPos);
}