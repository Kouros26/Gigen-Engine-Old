#include "Renderer.h"
#include "Skybox.h"
#include "GameObjectManager.h"
#include <ResourceManager.h>
#include "Application.h"

using namespace GigRenderer;

Skybox::Skybox()
{
    SetModel(g_SkyboxModelPath);
    SetTexture(g_SkyboxTexturePath);
    GetTransform().AddRotation(lm::FVec3(180, 0, 0));

    VertexShader* mainVertex = ResourceManager::Get<VertexShader>("Resources/Shaders/vertSkybox.vert");
    FragmentShader* mainFragment = ResourceManager::Get<FragmentShader>("Resources/Shaders/fragSkybox.frag");

    if (!shaderProgram.Link(mainVertex, mainFragment))
        std::cout << "Error linking main shader" << std::endl;

    ModelLocation = shaderProgram.GetUniform("model");
    viewProjLocation = shaderProgram.GetUniform("viewProj");
}

Skybox::~Skybox()
{
}

void Skybox::Draw()
{
    shaderProgram.Use();

    if (Application::IsInEditor() || Application::IsUsingEditorCam())
    {
        GetTransform().SetWorldPosition(Application::GetEditorCamera().GetTransform().GetWorldPosition());
    }
    else if(Camera* cam = GameObjectManager::GetCurrentCamera())
    {
        GetTransform().SetWorldPosition(cam->GetTransform().GetWorldPosition());
    }

    RENDERER.SetUniformValue(viewProjLocation, UniformType::MAT4, lm::FMat4::ToArray(Application::GetViewProj()));
    RENDERER.SetUniformValue(ModelLocation, UniformType::MAT4, lm::FMat4::ToArray(GetTransform().GetMatrix()));

    UpdateRender();

    shaderProgram.UnUse();
}