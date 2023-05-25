#include "SceneSaver.h"
#include "AudioSource.h"
#include "BoxRigidBody.h"
#include "CapsuleRigidBody.h"
#include "Component.h"
#include "GameObjectManager.h"
#include "Model.h"
#include "RigidBody.h"
#include "SphereRigidBody.h"
#include "Texture.h"
#include "Behaviour.h"
#include "WorldPhysics.h"
#include <fstream>
#include <filesystem>
#include <array>

void ProcessedObject::Clear()
{
	type.clear();
	name.clear();
	otherValues.clear();
	transform.clear();
	rigidBody.clear();
	parent.clear();
	components.clear();
	model.clear();
	texture.clear();

	componentSize = 0;
}

void Scene::SaveScene(const std::string& pSceneName)
{
	std::ofstream file(sceneFolder + pSceneName);

	if (GameObjectManager::GetSkyBox())
		file << formatting::skyboxTag << std::endl;

	for (int i = 0; i < GameObjectManager::GetSize(); i++)
	{
		GetValues(GameObjectManager::GetGameObject(i));
		file << formatting::typeTag << ProcessedObject::type << std::endl;

		if (IsLight(ProcessedObject::type))
		{
			file << formatting::lightValueTag << ProcessedObject::otherValues << std::endl;
			ProcessedObject::otherValues.clear();
		}

		else if (ProcessedObject::type == "Camera")
		{
			file << formatting::cameraValueTag << ProcessedObject::otherValues << std::endl;
			ProcessedObject::otherValues.clear();
		}

		file << formatting::nameTag << ProcessedObject::name << std::endl;
		file << formatting::transformTag << ProcessedObject::transform << std::endl;

		if (!ProcessedObject::rigidBody.empty())
			file << formatting::rigidBodyTag << ProcessedObject::rigidBody << std::endl;

		if (!ProcessedObject::parent.empty())
			file << formatting::parentTag << ProcessedObject::parent << std::endl;

		if (ProcessedObject::componentSize > 0)
			file << formatting::componentTag << std::to_string(ProcessedObject::componentSize) << ' ' << ProcessedObject::components << std::endl;

		if (!ProcessedObject::model.empty())
			file << formatting::modelTag << ProcessedObject::model << std::endl;

		if (!ProcessedObject::texture.empty())
			file << formatting::textureTag << ProcessedObject::texture << std::endl;

		ProcessedObject::Clear();
	}

	file.close();

	copy_file(sceneFolder + pSceneName, "../../../Resources/" + sceneFolder + pSceneName, std::filesystem::copy_options::update_existing);
}

void Scene::LoadScene(const std::string& pSceneName)
{
	std::ifstream file(sceneFolder + pSceneName);
	std::string line;
	GameObject* obj = nullptr;

	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		const std::string& word = line.substr(1);

		switch (line[0])
		{
		case '*':
			obj = ProcessTypeOfGameObject(word);
			break;

		case '.':
			ProcessLightData(word, obj);
			break;

		case '-':
			ProcessCameraData(word, dynamic_cast<Camera*>(obj));
			break;

		case 'N':
			obj->SetName(word);
			break;

		case 'W':
			ProcessTransform(word, obj);
			break;

		case 'R':
			ProcessRigidBody(word, obj);
			break;

		case 'P':
			parentChildMemory.emplace_back(word, obj->GetName());
			break;

		case 'C':
			if (word[1] != '0')
				ProcessComponents(word, obj);
			break;

		case 'M':
			obj->SetModel(word);
			break;

		case 'T':
			obj->SetTexture(word);
			break;

		case 'B':
			GameObjectManager::CreateSkyBox();
			break;

		default:
			break;
		}
	}

	for (const auto& i : parentChildMemory)
		GameObjectManager::FindObjectByName(i.first)->AddChild(*GameObjectManager::FindObjectByName(i.second));

	file.close();
	parentChildMemory.clear();
	currentScene = pSceneName;
}

void Scene::ReloadScene(const std::string& pSceneName)
{
	WorldPhysics::GetInstance().ClearCollisionCache();
	GameObjectManager::Cleanup();
	LoadScene(pSceneName);
}

std::string& Scene::GetCurrentSceneName()
{
	return currentScene;
}

Scene& Scene::GetInstance()
{
	static Scene scene;

	return scene;
}

void Scene::GetValues(GameObject* pGameObject)
{
	//type
	ProcessedObject::type = pGameObject->GetType();

	if (IsLight(ProcessedObject::type))
		GetLightValues(dynamic_cast<DirLight*>(pGameObject));

	else if (ProcessedObject::type == "Camera")
		GetCameraValues(dynamic_cast<Camera*>(pGameObject));

	//name
	ProcessedObject::name = pGameObject->GetName();

	//transform
	const lm::FVec3& position = pGameObject->GetTransform().GetWorldPosition();
	const lm::FVec3& rotation = pGameObject->GetTransform().GetWorldRotation();
	const lm::FVec3& scale = pGameObject->GetTransform().GetWorldScale();
	ProcessedObject::transform = VecToString(position) + ' ' + VecToString(rotation) + ' ' + VecToString(scale);

	//rigidbody
	if (pGameObject->GetRigidBody())
	{
		if (pGameObject->GetRigidBody()->GetShapeType() == RigidBodyType::BOX)
		{
			const auto boxBody = static_cast<BoxRigidBody*>(pGameObject->GetRigidBody());
			const lm::FVec3& halfExtents = boxBody->GetHalfExtents();
			ProcessedObject::rigidBody = "box " + VecToString(halfExtents);
		}

		else if (pGameObject->GetRigidBody()->GetShapeType() == RigidBodyType::CAPSULE)
		{
			const auto capsuleBody = static_cast<CapsuleRigidBody*>(pGameObject->GetRigidBody());
			const float capsuleRadius = capsuleBody->GetRadius();
			const float height = capsuleBody->GetHeight();
			ProcessedObject::rigidBody = "capsule " + std::to_string(capsuleRadius) + ' ' + std::to_string(height);
		}

		else if (pGameObject->GetRigidBody()->GetShapeType() == RigidBodyType::SPHERE)
		{
			const auto sphereBody = static_cast<SphereRigidBody*>(pGameObject->GetRigidBody());
			const float sphereRadius = sphereBody->GetRadius();
			ProcessedObject::rigidBody = "sphere " + std::to_string(sphereRadius);
		}

		const lm::FVec3& rbScale = pGameObject->GetRigidBody()->GetScale();
		const float mass = pGameObject->GetRigidBody()->GetMass();
		ProcessedObject::rigidBody += ' ' + VecToString(rbScale) + ' ' + std::to_string(mass);
		pGameObject->GetRigidBody()->IsGravityEnabled() ? ProcessedObject::rigidBody += " true" : ProcessedObject::rigidBody += " false";
	}

	//parent
	if (pGameObject->GetParent())
		ProcessedObject::parent = pGameObject->GetParent()->GetName();

	//components
	for (ProcessedObject::componentSize = 0; ProcessedObject::componentSize < pGameObject->GetComponentCount(); ProcessedObject::componentSize++)
	{
		Component* comp = pGameObject->GetComponentByID(ProcessedObject::componentSize);
		const std::string& component = comp->GetType();
		ProcessedObject::components += component + ' ';

		if (component == "GigScripting::Behaviour")
			ProcessedObject::components += static_cast<GigScripting::Behaviour*>(comp)->GetScriptName();

		else if (component == "AudioSource")
			GetAudioValues(static_cast<AudioSource*>(comp));

		ProcessedObject::components += ' ';
	}

	//model
	if (pGameObject->GetModel())
		ProcessedObject::model = pGameObject->GetModel()->GetFilePath();

	//texture
	if (pGameObject->GetTexture())
		ProcessedObject::texture = pGameObject->GetTexture()->GetFilePath();
}

void Scene::GetAudioValues(AudioSource* pAudioSource) const
{
	if (pAudioSource->GetAudio().empty())
		ProcessedObject::components += "none ";
	else
		ProcessedObject::components += pAudioSource->GetAudio() + ' ';

	pAudioSource->GetIs2D() ? ProcessedObject::components += "true " : ProcessedObject::components += "false ";
	pAudioSource->GetPlayOnStart() ? ProcessedObject::components += "true " : ProcessedObject::components += "false ";
	pAudioSource->GetIsLooping() ? ProcessedObject::components += "true " : ProcessedObject::components += "false ";

	ProcessedObject::components += std::to_string(pAudioSource->GetVolume()) + ' ';
	ProcessedObject::components += std::to_string(pAudioSource->GetMinDistance()) + ' ';
}

void Scene::GetLightValues(DirLight* pGameObject) const
{
	ProcessedObject::otherValues += VecToString(pGameObject->GetAmbient(), pGameObject->GetDiffuse(), pGameObject->GetSpecular());

	if (ProcessedObject::type == "PointLight")
	{
		const auto point = dynamic_cast<PointLight*>(pGameObject);
		ProcessedObject::otherValues += ' ' + VecToString(point->GetConstant(), point->GetLinear(), point->GetQuadratic());
	}

	else if (ProcessedObject::type == "SpotLight")
	{
		const auto spot = dynamic_cast<SpotLight*>(pGameObject);
		ProcessedObject::otherValues += ' ' + VecToString(spot->GetConstant(), spot->GetLinear(), spot->GetQuadratic());
		ProcessedObject::otherValues += ' ' + std::to_string(spot->GetCutOff()) + ' ' + std::to_string(spot->GetOuterCutOff());
	}

	ProcessedObject::otherValues += ' ' + VecToString(pGameObject->GetColor()[0], pGameObject->GetColor()[1], pGameObject->GetColor()[2]);
}

void Scene::GetCameraValues(const Camera* pGameObject) const
{
	ProcessedObject::otherValues += VecToString(pGameObject->GetFov(), pGameObject->GetNear(), pGameObject->GetFar())
		+ ' ' + std::to_string(pGameObject->GetRatio());
}

bool Scene::IsLight(const std::string& pType)
{
	if (pType == "DirLight" || pType == "SpotLight" || pType == "PointLight")
		return true;

	return false;
}

GameObject* Scene::ProcessTypeOfGameObject(const std::string& pLine)
{
	if (pLine == "GameObject")
		return GameObjectManager::CreateGameObject();

	if (IsLight(pLine))
	{
		if (pLine == "DirLight")
			return GameObjectManager::CreateDirLight();

		if (pLine == "PointLight")
			return GameObjectManager::CreatePointLight();

		return GameObjectManager::CreateSpotLight();
	}

	return GameObjectManager::CreateCamera();
}

void Scene::ProcessLightData(const std::string& pLine, GameObject* pOutGameObject)
{
	std::array<float, 11> data{};
	const std::vector<std::string> strings = SplitString(pLine);

	for (int i = 0; i < strings.size(); i++)
		data.at(i) = std::stof(strings[i]);

	const auto dir = dynamic_cast<DirLight*>(pOutGameObject);
	dir->SetAmbient(data[0]);
	dir->SetDiffuse(data[1]);
	dir->SetSpecular(data[2]);

	if (strings.size() == 6)
	{
		dir->SetColor({ data[3], data[4], data[5] });
		return;
	}

	const auto point = dynamic_cast<PointLight*>(pOutGameObject);
	point->SetConstant(data[3]);
	point->SetLinear(data[4]);
	point->SetQuadratic(data[5]);

	if (strings.size() == 9)
	{
		point->SetColor({ data[6], data[7], data[8] });
		return;
	}

	const auto spot = dynamic_cast<SpotLight*>(pOutGameObject);
	spot->SetCutOff(data[6]);
	spot->SetOuterCutOff(data[7]);
	spot->SetColor({ data[8], data[9], data[10] });
}

void Scene::ProcessCameraData(const std::string& pLine, Camera* pOutGameObject)
{
	std::array<float, 4> data{};
	const std::vector<std::string> strings = SplitString(pLine);

	for (int i = 0; i < strings.size(); i++)
		data.at(i) = std::stof(strings[i]);

	pOutGameObject->SetFov(data[0]);
	pOutGameObject->SetNear(data[1]);
	pOutGameObject->SetFar(data[2]);
	pOutGameObject->SetRatio(data[3]);
}

void Scene::ProcessTransform(const std::string& pLine, GameObject* pOutGameObject)
{
	std::array<float, 9> data{};
	const std::vector<std::string> strings = SplitString(pLine);

	for (int i = 0; i < strings.size(); i++)
		data.at(i) = std::stof(strings[i]);

	pOutGameObject->GetTransform() = Transform(lm::FVec3{ data[0], data[1], data[2] },
		lm::FVec3{ data[3], data[4], data[5] },
		lm::FVec3{ data[6], data[7], data[8] });
}

void Scene::ProcessRigidBody(const std::string& pLine, GameObject* pOutGameObject)
{
	const std::vector<std::string> strings = SplitString(pLine);

	if (strings[0] == "box")
	{
		pOutGameObject->CreateBoxRigidBody({ std::stof(strings[1]), std::stof(strings[2]), std::stof(strings[3]) },
			{ std::stof(strings[4]), std::stof(strings[5]), std::stof(strings[6]) },
			std::stof(strings[7]));

		if (strings[8] == "false")
			pOutGameObject->GetRigidBody()->SetGravityEnabled(false);
	}

	else if (strings[0] == "capsule")
	{
		pOutGameObject->CreateCapsuleRigidBody(std::stof(strings[1]), std::stof(strings[2]),
			{ std::stof(strings[3]), std::stof(strings[4]), std::stof(strings[5]) },
			std::stof(strings[6]));

		if (strings[7] == "false")
			pOutGameObject->GetRigidBody()->SetGravityEnabled(false);
	}

	else if (strings[0] == "sphere")
	{
		pOutGameObject->CreateSphereRigidBody(std::stof(strings[1]), { std::stof(strings[2]),
			std::stof(strings[3]), std::stof(strings[4]) }, std::stof(strings[5]));

		if (strings[6] == "false")
			pOutGameObject->GetRigidBody()->SetGravityEnabled(false);
	}
}

void Scene::ProcessComponents(const std::string& pLine, GameObject* pOutGameObject)
{
	const std::vector<std::string> strings = SplitString(pLine);

	for (int i = 1; i < strings.size(); i++)
	{
		if (strings[i].empty())
			continue;

		if (strings[i] == "AudioSource")
		{
			LoadSound(strings, pOutGameObject, i);
			i += 6;
		}

		else if (strings[i] == "GigScripting::Behaviour")
			pOutGameObject->AddComponent<GigScripting::Behaviour>(strings[i + 1]);
	}
}

void Scene::LoadSound(const std::vector<std::string>& pStrings, GameObject* pOutGameObject, int i) const
{
	const auto source = pOutGameObject->AddComponent<AudioSource>();

	if (pStrings[i + 1] != "none")
		source->SetAudio(pStrings[i + 1]);

	pStrings[i + 2] == "true" ? source->SetIs2D(true) : source->SetIs2D(false);
	pStrings[i + 3] == "true" ? source->SetPlayOnStart(true) : source->SetPlayOnStart(false);
	pStrings[i + 4] == "true" ? source->SetIsLooping(true) : source->SetIsLooping(false);
	source->SetVolume(stof(pStrings[i + 5]));
	source->SetMinDistance(stof(pStrings[i + 6]));
}

std::string Scene::VecToString(const float pFirst, const float pSecond, const float pThird) const
{
	return std::to_string(pFirst) + ' ' + std::to_string(pSecond) + ' ' + std::to_string(pThird);
}

std::string Scene::VecToString(const lm::FVec3& pVec) const
{
	return std::to_string(pVec.x) + ' ' + std::to_string(pVec.y) + ' ' + std::to_string(pVec.z);
}

std::vector<std::string> Scene::SplitString(const std::string& pString, char delimiter)
{
	int start = 0;
	int end = pString.find(delimiter);
	std::vector<std::string> strings;
	while (end != -1)
	{
		strings.push_back(pString.substr(start, end - start));
		start = end + 1;
		end = pString.find(delimiter, start);
	}
	strings.push_back(pString.substr(start, end - start));

	return strings;
}