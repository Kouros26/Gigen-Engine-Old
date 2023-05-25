#include "HierarchyDisplay.h"
#include "imgui.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "Application.h"
#include "InterfaceManager.h"

HierarchyDisplay::HierarchyDisplay()
{
	InterfaceManager::AddEditorElement(this);
}

HierarchyDisplay::~HierarchyDisplay()
= default;

void HierarchyDisplay::Draw()
{
	height = InterfaceManager::GetHeight();
	ImGui::SetNextWindowPos({ 0, g_menuBarSize });
	ImGui::SetNextWindowSize({ width, height });
	//noMove | NoCollapse
	ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);

	LimitWidthResize();
	ImGui::SetWindowSize("Scene", { width, height });
	CreatePopUp();
	DisplaySkybox();
	if (GameObjectManager::GetSize() > 0)
	{
		ImGui::SeparatorText("Objects");
		DisplayHierarchy();
	}

	if (UIManager::GetUISize() > 0 || UIManager::GetWorldSize() > 0)
	{
		ImGui::SeparatorText("UI");
		DisplayUI();
	}

	ImGui::BeginChild("##");
	ImGui::EndChild();

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("HIERARCHY"))
		{
			const auto drop = static_cast<GameObject*>(payload->Data);
			if (drop->GetParent())
			{
				drop->GetParent()->RemoveChild(*drop);
			}
		}

		ImGui::EndDragDropTarget();
	}

	ImGui::End();
}

void HierarchyDisplay::DisplayHierarchy() const
{
	for (int i = 0; i < GameObjectManager::GetSize(); i++)
	{
		DisplayGameObject(*GameObjectManager::GetGameObject(i), false);
	}
}

void HierarchyDisplay::DisplayUI() const
{
	for (int i = 0; i < UIManager::GetUISize(); i++)
	{
		DisplayUIElement(*UIManager::GetUIElement(i));
	}
	ImGui::SeparatorText("World");
	for (int i = 0; i < UIManager::GetWorldSize(); i++)
	{
		DisplayUIElement(*UIManager::GetWorldElement(i));
	}
}

void HierarchyDisplay::DisplayUIElement(UIElement & element) const
{
	const bool isFocused = (&element == UIManager::GetFocusedElement());
	int flags = ImGuiTreeNodeFlags_Leaf;

	if (isFocused)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, { 1,1,0.5f,1 });
	}

	ImGui::TreeNodeEx(element.GetName().c_str(), flags);

	if (isFocused)
	{
		ImGui::PopStyleColor();
	}

	ImGui::PushID(element.GetId());

	if (ImGui::IsItemClicked(0) && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing())
	{
		UIManager::SetFocusedElement(&element);
	}
	if (ImGui::IsItemClicked(1))
	{
		ImGui::OpenPopup(element.GetName().c_str());
	}

	if (ImGui::BeginPopup(element.GetName().c_str()))
	{
		ImGui::SeparatorText(element.GetName().c_str());
		if (ImGui::MenuItem(ICON_DESTROY " Destroy"))
		{
			UIManager::RemoveElement(&element);
		}
		if (ImGui::MenuItem(ICON_CLONE " Clone"))
		{
			UIManager::CreateUIElement(&element);
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
	ImGui::TreePop();
}

void HierarchyDisplay::DisplaySkybox() const
{
	GameObject* skybox = dynamic_cast<GameObject*>(GameObjectManager::GetSkyBox());
	const bool isFocused = (skybox == GameObjectManager::GetFocusedGameObject());
	int flags = ImGuiTreeNodeFlags_Leaf;

	if (isFocused)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, { 1,1,0.5f,1 });
	}

	ImGui::TreeNodeEx("SkyBox", flags);

	if (isFocused)
	{
		ImGui::PopStyleColor();
	}

	if (ImGui::IsItemClicked(0) && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing())
	{
		GameObjectManager::SetFocusedGameObject(skybox);
	}

	ImGui::TreePop();
}

void HierarchyDisplay::CreatePopUp() const
{
	if (ImGui::Button(ICON_PLUS " Create"))
		ImGui::OpenPopup("createPopUp");

	if (ImGui::BeginPopup("createPopUp"))
	{
		ImGui::SeparatorText("Create");
		if (ImGui::MenuItem("Empty"))
		{
			GameObjectManager::CreateGameObject();
		}
		if (ImGui::BeginMenu(ICON_GAMEOBJECT " Basics"))
		{
			if (ImGui::MenuItem("Arrow"))
			{
				GameObject* obj = GameObjectManager::CreateGameObject("Arrow");
				obj->SetModel("Engine/Models/Basics/Arrow.FBX");
			}
			if (ImGui::MenuItem("Capsule"))
			{
				GameObject* obj = GameObjectManager::CreateGameObject("Capsule");
				obj->SetModel("Engine/Models/Basics/Capsule.FBX");
			}
			if (ImGui::MenuItem("Cone"))
			{
				GameObject* obj = GameObjectManager::CreateGameObject("Cone");
				obj->SetModel("Engine/Models/Basics/Cone.FBX");
			}
			if (ImGui::MenuItem("Cube"))
			{
				GameObject* obj = GameObjectManager::CreateGameObject("Cube");
				obj->SetModel("Engine/Models/Basics/Cube.FBX");
			}
			if (ImGui::MenuItem("Cylinder"))
			{
				GameObject* obj = GameObjectManager::CreateGameObject("Cylinder");
				obj->SetModel("Engine/Models/Basics/Cylinder.FBX");
			}
			if (ImGui::MenuItem("Plane"))
			{
				GameObject* obj = GameObjectManager::CreateGameObject("Plane");
				obj->SetModel("Engine/Models/Basics/Plane.FBX");
			}
			if (ImGui::MenuItem("Sphere"))
			{
				GameObject* obj = GameObjectManager::CreateGameObject("Sphere");
				obj->SetModel("Engine/Models/Basics/Sphere.FBX");
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(ICON_LIGHT " Lights"))
		{
			if (ImGui::MenuItem("Directionnal Light"))
			{
				GameObjectManager::CreateDirLight();
			}
			if (ImGui::MenuItem("PointLight"))
			{
				GameObjectManager::CreatePointLight();
			}
			if (ImGui::MenuItem("SpotLight"))
			{
				GameObjectManager::CreateSpotLight();
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem(ICON_CAMERA " Camera"))
		{
			GameObjectManager::CreateCamera();
		}
		if (ImGui::BeginMenu(ICON_TEXTURE " UI"))
		{
			if (ImGui::MenuItem("Image"))
			{
				UIManager::AddImageElement();
			}
			if (ImGui::MenuItem("Text"))
			{
				UIManager::AddTextElement();
			}
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
}

void HierarchyDisplay::DisplayGameObject(GameObject & obj, bool isChild) const
{
	if (obj.GetParent() && !isChild)
	{
		return;
	}

	const bool isFocused = (&obj == GameObjectManager::GetFocusedGameObject());
	int flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;

	if (obj.GetChildrenCount() == 0)
	{
		flags = flags | ImGuiTreeNodeFlags_Leaf;
	}

	if (isFocused)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, { 1,1,0.5f,1 });
	}

	const bool treeNodeOpen = ImGui::TreeNodeEx(obj.GetName().c_str(), flags);

	if (isFocused)
	{
		ImGui::PopStyleColor();
	}

	ImGui::PushID(obj.GetId());

	GameObjectClicked(obj);
	GameObjectPopUp(obj);

	ImGui::PopID();

	if (ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("HIERARCHY", (const void*)&obj, sizeof(const void*));
		ImGui::Text(obj.GetName().c_str());

		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("HIERARCHY"))
		{
			const auto drop = static_cast<GameObject*>(payload->Data);
			if (drop != &obj && drop && !obj.IsAParent(drop))
			{
				if (drop->GetParent())
				{
					drop->GetParent()->RemoveChild(*drop);
				}
				obj.AddChild(*drop);
			}
		}

		ImGui::EndDragDropTarget();
	}

	if (treeNodeOpen)
	{
		for (int i = 0; i < obj.GetChildrenCount(); i++)
		{
			DisplayGameObject(*obj.GetChild(i), treeNodeOpen);
		}
		ImGui::TreePop();
	}
}

void HierarchyDisplay::GameObjectClicked(GameObject & obj) const
{
	if (ImGui::IsItemClicked(0) && (ImGui::GetMousePos().x - ImGui::GetItemRectMin().x) > ImGui::GetTreeNodeToLabelSpacing())
	{
		GameObjectManager::SetFocusedGameObject(&obj);
	}
	if (ImGui::IsItemClicked(1))
	{
		ImGui::OpenPopup(obj.GetName().c_str());
	}
	if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
	{
		EditorCamera& cam = Application::GetEditorCamera();
		cam.GetTransform().SetWorldPosition(obj.GetTransform().GetWorldPosition() - cam.GetFront() * 3);
	}
}

void HierarchyDisplay::GameObjectPopUp(GameObject & obj) const
{
	if (ImGui::BeginPopup(obj.GetName().c_str()))
	{
		ImGui::SeparatorText(obj.GetName().c_str());
		if (ImGui::MenuItem(ICON_DESTROY " Destroy"))
		{
			GameObjectManager::RemoveGameObject(&obj);
		}
		if (ImGui::MenuItem(ICON_REMOVE " UnParent"))
		{
			if (obj.GetParent())
			{
				obj.GetParent()->RemoveChild(obj);
			}
		}
		if (ImGui::MenuItem(ICON_CLONE " Clone"))
		{
			GameObjectManager::CreateGameObject(obj);
		}
		ImGui::EndPopup();
	}
}