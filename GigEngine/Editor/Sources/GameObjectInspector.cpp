#include "GameObjectInspector.h"
#include <fstream>

#include "Animator.h"
#include "UIManager.h"
#include "UIImage.h"
#include "UIText.h"
#include "AudioSource.h"
#include "InterfaceManager.h"
#include "ToolsDisplay.h"
#include "imgui.h"
#include "Application.h"
#include "Light.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "CapsuleRigidBody.h"
#include "SphereRigidBody.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "Behaviour.h"

GameObjectInspector::GameObjectInspector()
{
    InterfaceManager::AddEditorElement(this);
}

GameObjectInspector::~GameObjectInspector()
= default;

void GameObjectInspector::Draw()
{
    height = InterfaceManager::GetHeight() - InterfaceManager::GetClassHeight<ToolsDisplay>() - g_menuBarSize;
    ImGui::SetNextWindowPos({ InterfaceManager::GetWidth() - width, g_menuBarSize });
    ImGui::SetNextWindowSize({ width, height });

    // noMove et NoCollapse
    ImGui::Begin("Inspector", NULL, 4 | 32);

    LimitWidthResize();
    ImGui::SetWindowSize("Inspector", { width, height });

    DrawObject();

    ImGui::End();
}

void GameObjectInspector::DrawObject() const
{
    bool isGameObject = true;
    Object* object = GameObjectManager::GetFocusedGameObject();

    if (!object)
    {
        object = UIManager::GetFocusedElement();
        isGameObject = false;

        if (!object)
            return;
    }

    static char name[128];
    strcpy_s(name, object->GetName().c_str());

    ImGui::Text(ICON_GAMEOBJECT " Name"); ImGui::SameLine();

    if (ImGui::InputText("##1", name, 128))
    {
        object->SetName(name);
    }

    bool isActive = object->IsActive();
    ImGui::SameLine();
    ImGui::Checkbox("##2", &isActive);
    if (isActive != object->IsActive())
    {
        object->SetActive(isActive);
    }

    ImGui::Separator();

    if (isGameObject)
    {
        if (Skybox* sky = dynamic_cast<Skybox*>(object))
        {
            DrawSkyBox(sky);
        }
        else
        {
            DrawGameObject(dynamic_cast<GameObject*>(object));
            DrawDropTarget(dynamic_cast<GameObject*>(object));
        }
    }
    else
    {
        DrawUIElement(dynamic_cast<UIElement*>(object));
        DrawUIText(dynamic_cast<UIText*>(object));
        DrawDropTargetImage(dynamic_cast<UIImage*>(object));
    }
}

void GameObjectInspector::DrawGameObject(GameObject* pObject) const
{
    if (!pObject) return;

    DrawTransform(&pObject->GetTransform());
    DrawSpecials(pObject);

    if (pObject->GetRigidBody())
        DrawRigidBody(pObject);

    if (pObject->GetModel())
        DrawModel(pObject);

    DrawComponents(pObject);
    ImGui::Separator();
    DrawAddComponent(pObject);
}

void GameObjectInspector::DrawUIElement(UIElement* pUI) const
{
    if (!pUI) return;
    DrawRectTransform(&pUI->GetRectTransform());

    bool isWorld = pUI->GetIsWorld();
    if (isWorld)
        DrawTransform(&pUI->GetTransform());

    const lm::FVec3 col = pUI->GetColor();
    float color[3] = { col.x, col.y, col.z };

    ImGui::Text("World"); ImGui::SameLine();
    if (ImGui::Checkbox("##11", &isWorld))
    {
        pUI->SetIsWorld(isWorld);
    }

    ImGui::Text("Color"); ImGui::SameLine();
    if (ImGui::ColorEdit3("##10", color))
    {
        pUI->SetColor({ color[0],  color[1], color[2] });
    }
}

void GameObjectInspector::DrawRectTransform(RectTransform* rectTransform) const
{
    if (!rectTransform) return;

    if (ImGui::CollapsingHeader(ICON_TRANSFORM " RectTransform"))
    {
        const lm::FVec2 pos = rectTransform->GetPosition();
        const lm::FVec2 scl = rectTransform->GetSize();

        float translation[] = { pos.x, pos.y };
        float scale[] = { scl.x, scl.y };

        ImGui::Text("Position"); ImGui::SameLine();
        if (ImGui::DragFloat2("##30", translation, g_maxStep, g_floatMin, g_floatMax, g_floatFormat))
        {
            rectTransform->SetPosition(lm::FVec2(translation[0], translation[1]));
        }

        ImGui::Text("Size"); ImGui::SameLine();
        if (ImGui::DragFloat2("##31", scale, g_maxStep, g_floatMin, g_floatMax, g_floatFormat))
        {
            rectTransform->SetSize(lm::FVec2(scale[0], scale[1]));
        }

        ImGui::Text("Anchor X"); ImGui::SameLine();
        const char* itemsX[] = { "Left", "Center", "Right" };
        int item_currentX = (int)rectTransform->GetAnchorX();
        ImGui::Combo("##55", &item_currentX, itemsX, IM_ARRAYSIZE(itemsX));
        if (item_currentX != (int)rectTransform->GetAnchorX())
        {
            rectTransform->SetAnchorX((AnchorX)item_currentX);
        }

        ImGui::Text("Anchor Y"); ImGui::SameLine();
        const char* itemsY[] = { "Down", "Center", "Up" };
        int item_currentY = (int)rectTransform->GetAnchorY();
        ImGui::Combo("##56", &item_currentY, itemsY, IM_ARRAYSIZE(itemsY));
        if (item_currentY != (int)rectTransform->GetAnchorY())
        {
            rectTransform->SetAnchorY((AnchorY)item_currentY);
        }
    }
}

void GameObjectInspector::DrawDropTargetImage(UIImage* pImage) const
{
    if (!pImage) return;

    ImGui::BeginChild("##");
    ImGui::EndChild();

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
        {
            const char* path = static_cast<const char*>(payload->Data);
            const std::string str(path);
            if (str.find(".png") != std::string::npos ||
                str.find(".jpg") != std::string::npos ||
                str.find(".jpeg") != std::string::npos)
            {
                pImage->SetTexture(path);
            }
        }

        ImGui::EndDragDropTarget();
    }
}

void GameObjectInspector::DrawUIText(UIText* pText) const
{
    if (!pText) return;

    ImGui::Text("Text"); ImGui::SameLine();
    static char text[250];
    strcpy_s(text, pText->GetText().c_str());

    if (ImGui::InputText("##6", text, 250))
    {
        pText->SetText(text);
    }

    ImGui::BeginChild("##");
    ImGui::EndChild();

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
        {
            const char* path = static_cast<const char*>(payload->Data);
            const std::string str(path);
            if (str.find(".ttf") != std::string::npos)
            {
                pText->SetFont(path);
            }
        }

        ImGui::EndDragDropTarget();
    }
}

void GameObjectInspector::DrawSkyBox(Skybox* skybox) const
{
    if (!skybox) return;

    const lm::FVec3 rot = skybox->GetTransform().GetWorldRotation();
    float rotation[] = { rot.x, rot.y, rot.z };

    static bool lockRot = false;
    ImGui::Text("Rotation"); ImGui::SameLine();
    if (ImGui::Button(lockRot ? ICON_MD_LOCK "##6" : ICON_MD_LOCK_OPEN "##6"))
    {
        lockRot = !lockRot;
    }
    ImGui::SameLine();

    if (ImGui::DragFloat3("##7", rotation, g_maxStep, -360.0f, 360.0f, g_floatFormat))
    {
        if (lockRot)
        {
            LockCalculation(rotation, rot);
        }
        skybox->GetTransform().SetWorldRotation(lm::FVec3(rotation[0], rotation[1], rotation[2]));
    }

    const lm::FVec3 col = skybox->GetColor();
    float color[3] = { col.x, col.y, col.z };

    ImGui::Text("Color"); ImGui::SameLine();
    if (ImGui::ColorEdit3("##10", color))
    {
        skybox->SetColor({ color[0],  color[1], color[2] });
    }

    if (ImGui::CollapsingHeader(ICON_TEXTURE " Texture"))
    {
        std::string path;
        if (skybox->GetTexture())
        {
            path = skybox->GetTexture()->GetFilePath();
        }

        ImGui::Text("Path :"); ImGui::SameLine();
        ImGui::Text(path.c_str());
    }

    ImGui::BeginChild("##");
    ImGui::EndChild();

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
        {
            const char* path = static_cast<const char*>(payload->Data);
            const std::string str(path);
            if (str.find(".png") != std::string::npos ||
                str.find(".jpg") != std::string::npos ||
                str.find(".jpeg") != std::string::npos)
            {
                skybox->SetTexture(path);
            }
        }

        ImGui::EndDragDropTarget();
    }
}

void GameObjectInspector::DrawTransform(Transform* transform) const
{
    if (!transform) return;

    if (ImGui::CollapsingHeader(ICON_TRANSFORM " Transform"))
    {
        const lm::FVec3 rot = transform->GetLocalRotation();
        const lm::FVec3 pos = transform->GetLocalPosition();
        const lm::FVec3 scl = transform->GetLocalScale();

        float translation[] = { pos.x, pos.y, pos.z };
        float scale[] = { scl.x, scl.y, scl.z };
        float rotation[] = { rot.x, rot.y, rot.z };

        static bool lockPos = false;
        static bool lockRot = false;
        static bool lockScl = false;

        ImGui::Text("Position"); ImGui::SameLine();

        if (ImGui::Button(lockPos ? ICON_MD_LOCK "##1" : ICON_MD_LOCK_OPEN "##1"))
        {
            lockPos = !lockPos;
        }
        ImGui::SameLine();

        if (ImGui::DragFloat3("##3", translation, g_maxStep, g_floatMin, g_floatMax, g_floatFormat))
        {
            if (lockPos)
            {
                LockCalculation(translation, pos);
            }
            transform->SetWorldPosition(lm::FVec3(translation[0], translation[1], translation[2]));
        }

        ImGui::Text("Scale"); ImGui::SameLine();

        if (ImGui::Button(lockScl ? ICON_MD_LOCK "##2" : ICON_MD_LOCK_OPEN "##2"))
        {
            lockScl = !lockScl;
        }
        ImGui::SameLine();

        if (ImGui::DragFloat3("##4", scale, g_maxStep, 0.000000001f, g_floatMax, g_floatFormat))
        {
            if (lockScl)
            {
                LockCalculation(scale, scl);
            }
            transform->SetWorldScale(lm::FVec3(scale[0], scale[1], scale[2]));
        }

        ImGui::Text("Rotation"); ImGui::SameLine();

        if (ImGui::Button(lockRot ? ICON_MD_LOCK "##3" : ICON_MD_LOCK_OPEN "##3"))
        {
            lockRot = !lockRot;
        }
        ImGui::SameLine();

        if (ImGui::DragFloat3("##5", rotation, g_maxStep, -360.0f, 360.0f, g_floatFormat))
        {
            if (lockRot)
            {
                LockCalculation(rotation, rot);
            }
            transform->SetWorldRotation(lm::FVec3(rotation[0], rotation[1], rotation[2]));
        }
    }
}

void GameObjectInspector::DrawModel(GameObject* pObject) const
{
    if (ImGui::CollapsingHeader(ICON_MODEL " Model"))
    {
        if (ImGui::IsItemClicked(1))
        {
            ImGui::OpenPopup("ModelPopUp");
        }

        if (ImGui::BeginPopup("ModelPopUp"))
        {
            ImGui::SeparatorText("Model");
            if (ImGui::MenuItem("Remove"))
            {
                pObject->SetModel(nullptr);
            }
            ImGui::EndPopup();
            if (!pObject->GetModel())
            {
                return;
            }
        }

        const std::string path = pObject->GetModel()->GetFilePath();

        ImGui::Text("Path :"); ImGui::SameLine();
        ImGui::Text(path.c_str());

        if (pObject->GetModel())
        {
            DrawTexture(pObject);
        }
    }
}

void GameObjectInspector::DrawTexture(const GameObject* pObject) const
{
    ImGui::SetCursorPosX(30);
    ImGui::BeginGroup();
    if (ImGui::CollapsingHeader(ICON_TEXTURE " Texture"))
    {
        std::string path;
        if (pObject->GetTexture())
        {
            path = pObject->GetTexture()->GetFilePath();
        }

        ImGui::Text("Path :"); ImGui::SameLine();
        ImGui::Text(path.c_str());
    }
    ImGui::EndGroup();
}

void GameObjectInspector::DrawRigidBody(GameObject* pObject) const
{
    if (ImGui::CollapsingHeader(ICON_RIGIDBODY " RigidBody"))
    {
        if (ImGui::IsItemClicked(1))
        {
            ImGui::OpenPopup("RigidPopUp");
        }

        if (ImGui::BeginPopup("RigidPopUp"))
        {
            ImGui::SeparatorText("RigidBody");
            if (ImGui::MenuItem("Remove"))
            {
                pObject->RemoveRigidBody();
            }
            ImGui::EndPopup();
            if (!pObject->GetRigidBody())
            {
                return;
            }
        }

        RigidBody* rigid = pObject->GetRigidBody();

        ImGui::Text("Mass"); ImGui::SameLine();
        btScalar mass = rigid->GetMass();
        if (ImGui::DragFloat("##18", &mass, g_maxStep, 0, g_floatMax, g_floatFormat))
        {
            rigid->SetMass(mass);
        }

        ImGui::Text("Gravity"); ImGui::SameLine();
        bool grav = rigid->IsGravityEnabled();
        ImGui::Checkbox("##19", &grav);
        if (grav != rigid->IsGravityEnabled())
        {
            rigid->SetGravityEnabled(grav);
        }

        ImGui::Text("Collision type"); ImGui::SameLine();
        const char* items[] = { "Dynamic", "Kinetic", "Static", "Trigger"};
        int item_current = rigid->GetCollisionFlag();
        ImGui::Combo("##20", &item_current, items, IM_ARRAYSIZE(items));
        if (item_current != rigid->GetCollisionFlag())
        {
            rigid->SetRBState(static_cast<RBState>(item_current));
        }

        ImGui::SetCursorPosX(30);
        ImGui::BeginGroup();
        DrawRigidShape(rigid);
        //DrawRigidTransform(rigid);
        ImGui::EndGroup();
    }
}

void GameObjectInspector::DrawRigidShape(RigidBody* body) const
{
    if (body->GetShapeType() != RigidBodyType::BOX)
    {
        if (ImGui::CollapsingHeader(ICON_MD_SHAPE_LINE "Shape"))
        {
            if (body->GetShapeType() == RigidBodyType::CAPSULE)
            {
                const auto caps = static_cast<CapsuleRigidBody*>(body);
                float radius = caps->GetRadius();
                float height = caps->GetHeight();

                ImGui::Text("Radius"); ImGui::SameLine();
                if (ImGui::DragFloat("##21", &radius, g_maxStep, 0.001f, g_floatMax, g_floatFormat))
                {
                    caps->SetRadius(radius);
                }
                ImGui::Text("Height"); ImGui::SameLine();
                if (ImGui::DragFloat("##22", &height, g_maxStep, 0.001f, g_floatMax, g_floatFormat))
                {
                    caps->SetHeight(height);
                }
            }
            else if (body->GetShapeType() == RigidBodyType::SPHERE)
            {
                const auto sphere = static_cast<SphereRigidBody*>(body);
                float radius = sphere->GetRadius();

                ImGui::Text("Radius"); ImGui::SameLine();
                if (ImGui::DragFloat("##23", &radius, g_maxStep, 0.001f, g_floatMax, g_floatFormat))
                {
                    sphere->SetRadius(radius);
                }
            }
        }
    }
}

void GameObjectInspector::DrawRigidTransform(RigidBody* body) const
{
    if (ImGui::CollapsingHeader(ICON_TRANSFORM "Transform##2"))
    {
        //lock bool
        static bool lockRigidPos = false;
        static bool lockRigidScl = false;
        static bool lockRigidRot = false;

        //position var
        const btVector3 btPos = body->GetTransfrom().getOrigin();
        float translation[3] = { btPos.getX(), btPos.getY(), btPos.getZ() }; //need for DragFloat3
        const lm::FVec3 pos = { btPos.getX(), btPos.getY(), btPos.getZ() }; //need for lock

        //scale var
        float scale[3] = { body->GetScale().x, body->GetScale().y, body->GetScale().z }; //need for DragFloat3
        const lm::FVec3 scl = { body->GetScale().x, body->GetScale().y, body->GetScale().z }; //need for lock

        //rotation var
        float rotation[3];
        body->GetTransfrom().getRotation().getEulerZYX((btScalar&)rotation[2], (btScalar&)rotation[1], (btScalar&)rotation[0]); //need for DragFloat3
        const lm::FVec3 rot(rotation[0], rotation[1], rotation[2]); //need for lock

        //position widget
        ImGui::Text("Position"); ImGui::SameLine();
        if (ImGui::Button(lockRigidPos ? ICON_MD_LOCK "##4" : ICON_MD_LOCK_OPEN "##4"))
        {
            lockRigidPos = !lockRigidPos;
        }
        ImGui::SameLine();

        if (ImGui::DragFloat3("##21", translation, g_maxStep, g_floatMin, g_floatMax, g_floatFormat))
        {
            if (lockRigidPos)
            {
                LockCalculation(translation, pos);
            }
            body->SetRigidBodyPosition(lm::FVec3(translation[0], translation[1], translation[2]));
        }

        //scale widget
        ImGui::Text("Scale"); ImGui::SameLine();

        if (ImGui::Button(lockRigidScl ? ICON_MD_LOCK "##5" : ICON_MD_LOCK_OPEN "##5"))
        {
            lockRigidScl = !lockRigidScl;
        }
        ImGui::SameLine();

        if (ImGui::DragFloat3("##22", scale, g_maxStep, 0.001f, g_floatMax, g_floatFormat))
        {
            if (lockRigidScl)
            {
                LockCalculation(scale, scl);
            }
            body->SetRigidBodyScale(lm::FVec3(scale[0], scale[1], scale[2]));
        }

        //rotation widget
        ImGui::Text("Rotation"); ImGui::SameLine();

        if (ImGui::Button(lockRigidRot ? ICON_MD_LOCK "##6" : ICON_MD_LOCK_OPEN "##6"))
        {
            lockRigidRot = !lockRigidRot;
        }
        ImGui::SameLine();

        if (ImGui::DragFloat3("##23", rotation, g_maxStep, -360.0f, 360.0f, g_floatFormat))
        {
            if (lockRigidRot)
            {
                LockCalculation(rotation, rot);
            }
            body->SetRigidBodyRotation(lm::FVec3(rotation[0], rotation[1], rotation[2]));
        }
    }
}

void GameObjectInspector::DrawSpecials(GameObject* pObject) const
{
    if (auto light = dynamic_cast<DirLight*>(pObject))
    {
        DrawLight(pObject);
        return;
    }

    if (const auto cam = dynamic_cast<Camera*>(pObject))
        DrawCamera(cam);
}

void GameObjectInspector::DrawComponents(GameObject* pObject) const
{
	DrawScriptsComponent(pObject);
	DrawAudiosComponent(pObject);
	DrawAnimationsComponent(pObject);
}

void GameObjectInspector::DrawLight(GameObject* pObject) const
{
    const auto dirlight = dynamic_cast<DirLight*>(pObject);
    if (ImGui::CollapsingHeader(ICON_LIGHT " Light"))
    {
        float* color = dirlight->GetColor();
        float ambient = dirlight->GetAmbient();
        float diffuse = dirlight->GetDiffuse();
        float specular = dirlight->GetSpecular();

        ImGui::Text("Color"); ImGui::SameLine();
        ImGui::ColorEdit3("##6", color);

        ImGui::Text("Ambient"); ImGui::SameLine();
        if (ImGui::DragFloat("##7", &ambient, g_maxStep, 0, g_floatMax, g_floatFormat))
        {
            dirlight->SetAmbient(ambient);
        }

        ImGui::Text("Diffuse"); ImGui::SameLine();
        if (ImGui::DragFloat("##8", &diffuse, g_maxStep, 0, g_floatMax, g_floatFormat))
        {
            dirlight->SetDiffuse(diffuse);
        }

        ImGui::Text("Specular"); ImGui::SameLine();
        if (ImGui::DragFloat("##9", &specular, g_maxStep, 0, g_floatMax, g_floatFormat))
        {
            dirlight->SetSpecular(specular);
        }

        if (const auto pointLight = dynamic_cast<PointLight*>(pObject))
        {
            float constant = pointLight->GetConstant();
            float linear = pointLight->GetLinear();
            float quadratic = pointLight->GetQuadratic();

            ImGui::Text("Constant"); ImGui::SameLine();
            if (ImGui::DragFloat("##10", &constant, g_maxStep, 0, g_floatMax, g_floatFormat))
            {
                pointLight->SetConstant(constant);
            }

            ImGui::Text("Linear"); ImGui::SameLine();
            if (ImGui::DragFloat("##11", &linear, g_maxStep, 0, g_floatMax, g_floatFormat))
            {
                pointLight->SetLinear(linear);
            }

            ImGui::Text("Quadratic"); ImGui::SameLine();
            if (ImGui::DragFloat("##12", &quadratic, g_maxStep, 0, g_floatMax, g_floatFormat))
            {
                pointLight->SetQuadratic(quadratic);
            }
        }

        if (const auto spotLight = dynamic_cast<SpotLight*>(pObject))
        {
            float cutOff = spotLight->GetCutOff();
            float outerCutOff = spotLight->GetOuterCutOff();

            ImGui::Text("CutOff"); ImGui::SameLine();
            if (ImGui::DragFloat("##13", &cutOff, g_maxStep, 0, g_floatMax, g_floatFormat))
            {
                spotLight->SetCutOff(cutOff);
            }

            ImGui::Text("OuterCutOff"); ImGui::SameLine();
            if (ImGui::DragFloat("##14", &outerCutOff, g_maxStep, 0, g_floatMax, g_floatFormat))
            {
                spotLight->SetOuterCutOff(outerCutOff);
            }
        }
    }
}

void GameObjectInspector::DrawCamera(Camera* pObject) const
{
    float fov = pObject->GetFov();
    float tNear = pObject->GetNear();
    float tFar = pObject->GetFar();

    if (ImGui::CollapsingHeader(ICON_CAMERA " Camera"))
    {
        ImGui::Text("Fov"); ImGui::SameLine();
        if (ImGui::DragFloat("##15", &fov, g_maxStep, 0, g_floatMax, g_floatFormat))
        {
            pObject->SetFov(fov);
        }

        ImGui::Text("Near"); ImGui::SameLine();
        if (ImGui::DragFloat("##16", &tNear, g_maxStep, 0, g_floatMax, g_floatFormat))
        {
            pObject->SetNear(tNear);
        }

        ImGui::Text("Far"); ImGui::SameLine();
        if (ImGui::DragFloat("##17", &tFar, g_maxStep, 0, g_floatMax, g_floatFormat))
        {
            pObject->SetFar(tFar);
        }
    }
}

void GameObjectInspector::DrawAddComponent(GameObject* pObject) const
{
    const ImGuiStyle& style = ImGui::GetStyle();

    const float size = ImGui::CalcTextSize("Add component " ICON_PLUS).x + style.FramePadding.x * 2.0f;
    const float avail = ImGui::GetContentRegionAvail().x;

    const float off = (avail - size) * 0.5f;
    if (off > 0.0f)
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);

    if (ImGui::Button("Add component " ICON_PLUS))
    {
        ImGui::OpenPopup("addComponentPopUp");
    }

    if (ImGui::BeginPopup("addComponentPopUp"))
    {
        ImGui::SeparatorText("Components");

		if (ImGui::MenuItem(ICON_MD_ANIMATION " Animator"))
		{
			pObject->AddComponent<Animator>();
		}

		if (ImGui::MenuItem(ICON_MD_AUDIO_FILE " Audio source"))
		{
			pObject->AddComponent<AudioSource>();
		}

        if (!pObject->GetModel())
        {
            if (ImGui::MenuItem(ICON_MODEL " Model"))
            {
                pObject->SetModel(g_defaultModelPath);
            }
        }

        if (!pObject->GetRigidBody())
        {
            if (ImGui::BeginMenu(ICON_RIGIDBODY "RigidBody"))
            {
                if (ImGui::MenuItem("Capsule"))
                {
                    pObject->CreateCapsuleRigidBody(1, 2, { 1 }, 1);
                }
                if (ImGui::MenuItem("Cube"))
                {
                    pObject->CreateBoxRigidBody({ 1 }, { 1 }, 1);
                }
                if (ImGui::MenuItem("Sphere"))
                {
                    pObject->CreateSphereRigidBody(1, { 1 }, 1);
                }
                ImGui::EndMenu();
            }
        }

        if (ImGui::MenuItem(ICON_COMPONENT " Scripts"))
        {
            pObject->AddScript();
        }

        ImGui::EndPopup();
    }
}

void GameObjectInspector::DrawScriptsComponent(GameObject* pObject) const
{
    std::vector<GigScripting::Behaviour*> scripts;
    pObject->GetComponents<GigScripting::Behaviour>(scripts);
    if (scripts.empty())
        return;

    using namespace GigScripting;
    if (ImGui::CollapsingHeader(ICON_COMPONENT " Scripts"))
    {
        for (const auto& script : scripts)
        {
            if (!script)
            {
                return;
            }
            const std::string& name = script->GetScriptName();
            if (ImGui::TreeNode(name.c_str()))
            {
                ImGui::Text(ReadScript("../../../Resources/Editor/Scripts/" + name).c_str());
                if (ImGui::IsItemClicked(1))
                {
                    ImGui::OpenPopup("ScriptPopUp");
                }

                if (ImGui::BeginPopup("ScriptPopUp"))
                {
                    ImGui::SeparatorText("Script");
                    if (ImGui::MenuItem("Remove"))
                    {
                        pObject->RemoveScript(script);
                    }
                    ImGui::EndPopup();
                }

                ImGui::TreePop();
            }
        }
    }

    scripts.clear();
}

void GameObjectInspector::DrawAudiosComponent(GameObject* pObject) const
{
    std::vector<AudioSource*> audios;
    pObject->GetComponents<AudioSource>(audios);
    if (audios.empty())
    {
        return;
    }

    const char* temp = ICON_MD_AUDIO_FILE " Audio source##";

    for (int i = 0; i < audios.size(); i++)
    {
        AudioSource* source = audios[i];
        if (!source)
        {
            return;
        }

        char name[128];
        std::string num = std::to_string(i);
        strcpy(name, temp);
        strcat(name, num.c_str());

        char popUpName[128] = "AudioPopUp##";
        strcat(popUpName, num.c_str());

        if (ImGui::CollapsingHeader(name))
        {
            if (ImGui::IsItemClicked(1))
            {
                ImGui::OpenPopup(popUpName);
            }

            if (ImGui::BeginPopup(popUpName))
            {
                ImGui::SeparatorText("Audio Source");
                if (ImGui::MenuItem("Remove"))
                {
                    pObject->RemoveComponent<AudioSource>(source);
                    ImGui::EndPopup();
                    return;
                }
                ImGui::EndPopup();
            }

            std::string audioPath = source->GetAudio();
            if (audioPath.length() == 0) audioPath = "Drop mp3 file here";

            ImGui::Text(audioPath.c_str());

            if (ImGui::BeginDragDropTarget())
            {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
                {
                    const char* path = static_cast<const char*>(payload->Data);
                    const std::string str(path);
                    if (str.find(".mp3") != std::string::npos)
                    {
                        source->SetAudio(path);
                    }
                }

                ImGui::EndDragDropTarget();
            }

            bool is2D = source->GetIs2D();
            bool playOnStart = source->GetPlayOnStart();
            bool loop = source->GetIsLooping();
            float volume = source->GetVolume();
            float minDistance = source->GetMinDistance();

            char soundName[128] = "##2DSOUND";
            strcat(soundName, num.c_str());
            ImGui::Text("2D sound"); ImGui::SameLine();
            if (ImGui::Checkbox(soundName, &is2D))
            {
                source->SetIs2D(is2D);
            }

            char startName[128] = "##start";
            strcat(startName, num.c_str());
            ImGui::Text("Play on start"); ImGui::SameLine();
            if (ImGui::Checkbox(startName, &playOnStart))
            {
                source->SetPlayOnStart(playOnStart);
            }

            char loopName[128] = "##loop";
            strcat(loopName, num.c_str());
            ImGui::Text("Loop"); ImGui::SameLine();
            if (ImGui::Checkbox(loopName, &loop))
            {
                source->SetIsLooping(loop);
            }

            char volumeName[128] = "##vol";
            strcat(volumeName, num.c_str());
            ImGui::Text("Volume"); ImGui::SameLine();
            if (ImGui::DragFloat(volumeName, &volume, g_maxStep, 0, 1, g_floatFormat))
            {
                source->SetVolume(volume);
            }

            if (!is2D)
            {
                char minName[128] = "##min";
                strcat(minName, num.c_str());
                ImGui::Text("Min distance"); ImGui::SameLine();
                if (ImGui::DragFloat(minName, &minDistance, g_maxStep, 0, g_floatMax, g_floatFormat))
                {
                    source->SetMinDistance(minDistance);
                }
            }
        }
    }
}

void GameObjectInspector::DrawAnimationsComponent(GameObject* pObject) const
{
	std::vector<Animator*> animators;
	pObject->GetComponents<Animator>(animators);
	if (animators.empty())
		return;

	const char* temp = ICON_MD_ANIMATION " Animator##";

	for (int i = 0; i < animators.size(); i++)
	{
		Animator* animator = animators[i];

		if (!animator)
			return;

		char name[128];
		std::string num = std::to_string(i);
		strcpy(name, temp);
		strcat(name, num.c_str());

		char popUpName[128] = "AnimationPopUp##";
		strcat(popUpName, num.c_str());

		std::vector<AnimationState> states;
		animator->MapStates(states);

		if (ImGui::CollapsingHeader(name))
		{
			if (ImGui::IsItemClicked(1))
				ImGui::OpenPopup(popUpName);

			if (ImGui::BeginPopup(popUpName))
			{
				ImGui::SeparatorText("Animator");
				if (ImGui::MenuItem("Remove"))
				{
					pObject->RemoveComponent<Animator>(animator);
					ImGui::EndPopup();
					return;
				}
				ImGui::EndPopup();
			}

			ImGui::SetCursorPosX(30);
			ImGui::BeginGroup();
			for (int j = 0; j < states.size(); j++)
			{
				if (ImGui::CollapsingHeader(states[j].stateName.c_str()))
				{
					if (states[j].stateAnim) 
					{
						ImGui::SetCursorPosX(50);
						ImGui::BeginGroup();
						ImGui::Text(states[j].stateAnim->GetFilePath().c_str());
						ImGui::EndGroup();
					}
				}

				if (ImGui::IsItemClicked(1))
					ImGui::OpenPopup(states[j].stateName.c_str());

				if (ImGui::BeginPopup(states[j].stateName.c_str()))
				{
					ImGui::SeparatorText(states[j].stateName.c_str());
					if (ImGui::MenuItem("Remove"))
					{
						animator->RemoveState(states[j].stateName);
						ImGui::EndPopup();
						return;
					}
					ImGui::EndPopup();
				}
			}
			ImGui::EndGroup();
		}
	}
}

void GameObjectInspector::DrawDropTarget(GameObject * pObject) const
{
    ImGui::BeginChild("##");
    ImGui::EndChild();

    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
        {
            const char* path = static_cast<const char*>(payload->Data);
            const std::string str(path);
            if (str.find(".obj") != std::string::npos
                || str.find(".OBJ") != std::string::npos
                || str.find(".fbx") != std::string::npos
                || str.find(".FBX") != std::string::npos)
            {
                pObject->SetModel(path);
            }
            else if (str.find(".png") != std::string::npos ||
                str.find(".jpg") != std::string::npos ||
                str.find(".jpeg") != std::string::npos)
            {
                pObject->SetTexture(path);
            }
            else if (str.find(".lua") != std::string::npos)
            {
                pObject->AddScript(path);
            }
            else if (str.find(".mp3") != std::string::npos)
            {
                auto* temp = pObject->AddComponent<AudioSource>();
                temp->SetAudio(str);
            }
        }

        ImGui::EndDragDropTarget();
    }
}

void GameObjectInspector::LockCalculation(float* fvec3, const lm::FVec3& original) const
{
    bool isZero = false;
    float val = 1;
    for (int i = 0; i < 3; i++)
    {
        if (fvec3[i] != original[i])
        {
            if (original[i] == 0)
            {
                isZero = true;
                val = fvec3[i];
            }
            else
            {
                val = fvec3[i] / original[i];
            }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (isZero)
        {
            fvec3[i] = val;
        }
        else
        {
            fvec3[i] = original[i] * val;
        }
    }
}

std::string GameObjectInspector::ReadScript(const std::string& pPath) const
{
    std::ifstream file(pPath + ".lua");
    if (!file.is_open()) {
        return "Failed to open file: " + pPath;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}