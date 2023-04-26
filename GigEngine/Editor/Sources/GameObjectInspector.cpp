#include "GameObjectInspector.h"
#include "InterfaceManager.h"
#include "FileDisplay.h"
#include "imgui.h"
#include "Application.h"
#include "Light.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "GameObjectManager.h"
#include <Windows.h>

GameObjectInspector::GameObjectInspector()
{
	InterfaceManager::AddEditorElement(this);
}

GameObjectInspector::~GameObjectInspector()
= default;

void GameObjectInspector::Draw()
{
	height = InterfaceManager::GetHeight() - InterfaceManager::GetClassHeight<FileDisplay>() - g_menuBarSize;
	ImGui::SetNextWindowPos({ InterfaceManager::GetWidth() - width, g_menuBarSize });
	ImGui::SetNextWindowSize({ width, height });

	// noMove et NoCollapse
	ImGui::Begin("Inspector", NULL, 4 | 32);

	LimitWidthResize();
	ImGui::SetWindowSize("Inspector", { width, height });

	DrawGameObject();

	ImGui::End();
}

void GameObjectInspector::DrawGameObject()
{
	GameObject* object = GameObjectManager::GetFocusedGameObject();
	if (!object) return;

	static char name[128];
	strcpy_s(name, object->GetName().c_str());

	ImGui::Text("Name"); ImGui::SameLine();

	if (ImGui::InputText("##1", name, 128))
	{
		object->SetName(name);
	}

	ImGui::SameLine(); 
	ImGui::Checkbox("##2", object->IsActiveP());

	ImGui::Separator();

	DrawTransform(object);
	DrawSpecials(object);
	DrawComponents(object);
	DrawModel(object);
}

void GameObjectInspector::DrawTransform(GameObject * pObject) const
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		const lm::FVec3 rot = pObject->GetTransform().GetWorldRotation();
		const lm::FVec3 pos = pObject->GetTransform().GetWorldPosition();
		const lm::FVec3 scl = pObject->GetTransform().GetWorldScale();

		float translation[] = { pos.x, pos.y, pos.z };
		float scale[] = { scl.x, scl.y, scl.z };
		float rotation[] = { rot.x, rot.y, rot.z };

		ImGui::Text("Position"); ImGui::SameLine();

		if (ImGui::DragFloat3("##3", translation, g_maxStep, g_floatMin, g_floatMax, g_floatFormat))
		{
			pObject->GetTransform().SetWorldPosition(lm::FVec3(translation[0], translation[1], translation[2]));
		}

		ImGui::Text("Scale"); ImGui::SameLine();
		if (ImGui::DragFloat3("##4", scale, g_maxStep, 0.001f, g_floatMax, g_floatFormat))
		{
			pObject->GetTransform().SetWorldScale(lm::FVec3(scale[0], scale[1], scale[2]));
		}

		ImGui::Text("Rotation"); ImGui::SameLine();
		if (ImGui::DragFloat3("##5", rotation, g_maxStep, -360.0f, 360.0f, g_floatFormat))
		{
			pObject->GetTransform().SetWorldRotation(lm::FVec3(rotation[0], rotation[1], rotation[2]));
		}
	}
}

void GameObjectInspector::DrawModel(GameObject * pObject) const
{
	if (ImGui::CollapsingHeader("Model"))
	{
		std::string path;
		if (pObject->GetModel())
		{
			path = pObject->GetModel()->GetFilePath();
		}

		ImGui::Text("Path :"); ImGui::SameLine();
		ImGui::Text(path.c_str());

		if (ImGui::Button("Locate##1"))
		{
			const std::string& filePath = GetFilePathFromExplorer("3D object \0 *.obj\0 *.OBJ\0 *.fbx\0 *.FBX\0");

			if (filePath.length() > 0)
				pObject->SetModel(filePath);
		}

		if (pObject->GetModel())
		{
			DrawTexture(pObject);
		}
	}
}

void GameObjectInspector::DrawTexture(GameObject * pObject) const
{
	if (ImGui::CollapsingHeader("Texture"))
	{
		std::string path;
		if (pObject->GetTexture())
		{
			path = pObject->GetTexture()->GetFilePath();
		}

		ImGui::Text("Path :"); ImGui::SameLine();
		ImGui::Text(path.c_str());

		if (ImGui::Button("Locate##2"))
		{
			const std::string& filePath = GetFilePathFromExplorer("image \0 *.png\0 *.jpeg\0 *.jpg\0");

			if (filePath.length() > 0)
				pObject->SetTexture(filePath);
		}
	}
}

void GameObjectInspector::DrawSpecials(GameObject * pObject) const
{
	if (auto light = dynamic_cast<DirLight*>(pObject))
	{
		DrawLight(pObject);
		return;
	}

	if (const auto cam = dynamic_cast<Camera*>(pObject))
		DrawCamera(cam);
}

void GameObjectInspector::DrawComponents(GameObject * pObject)
{
	//TO DO
}

void GameObjectInspector::DrawLight(GameObject * pObject) const
{
	const auto dirlight = dynamic_cast<DirLight*>(pObject);
	if (ImGui::CollapsingHeader("Light"))
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

void GameObjectInspector::DrawCamera(Camera * pObject) const
{
	float fov = pObject->GetFov();
	float tNear = pObject->GetNear();
	float tFar = pObject->GetFar();

	if (ImGui::CollapsingHeader("Camera"))
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

std::string GameObjectInspector::GetFilePathFromExplorer(const char* filter)
{
	OPENFILENAME ofn;
	char fileName[1000] = "";
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = filter;
	ofn.nMaxFile = 1000;
	ofn.lpstrFile = fileName;
	ofn.Flags = OFN_FILEMUSTEXIST;
	ofn.lpstrDefExt = "";

	if (GetOpenFileName(&ofn))
		return std::string(fileName);

	return std::string();
}