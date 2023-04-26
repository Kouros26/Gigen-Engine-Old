#include "GameObjectManager.h"
#include "Camera.h"
#include "Light.h"
#include "RigidBody.h"
#include <algorithm>

GameObjectManager::GameObjectManager()
{}

GameObjectManager::~GameObjectManager()
{}

unsigned int GameObjectManager::GetSize()
{
	return static_cast<unsigned>(gameObjects.size());
}

GameObject*& GameObjectManager::GetGameObject(int i)
{
	return gameObjects[i];
}

void GameObjectManager::Cleanup()
{
	for (int i = 0; i < GameObjectManager::GetSize(); i++)
		delete gameObjects[i];
}

GameObject* GameObjectManager::CreateGameObject()
{
	const auto object = new GameObject();

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreateGameObject(const std::string& name)
{
	const auto object = new GameObject(name);

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreateGameObject(const std::string& name, const lm::FVec3& position,
	const lm::FVec3& rotation, const lm::FVec3& scale)
{
	const auto object = new GameObject(name, position, rotation, scale);

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreateGameObject(const lm::FVec3& position, const lm::FVec3& rotation,
	const lm::FVec3& scale)
{
	const auto object = new GameObject(position, rotation, scale);

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreateGameObject(const GameObject& other)
{
	const auto object = new GameObject(other);

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreateGameObject(const GameObject* other)
{
	const auto object = new GameObject(*other);

	return AddGameObject(object);
}

GameObject& GameObjectManager::operator=(const GameObject& other)
{
	const auto object = new GameObject(other);

	return *AddGameObject(object);
}

GameObject* GameObjectManager::CreateSpotLight(float ambient, float diffuse, float specular,
	float constant, float linear, float quadratic,
	float cutOff, float outerCutOff,
	lm::FVec3 color)
{
	if (spotLights.size() >= g_nbMaxLight)
		return nullptr;

	SpotLight* object = new SpotLight(ambient, diffuse, specular, constant, linear, quadratic, cutOff, outerCutOff, color);
	spotLights.push_back(object);

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreatePointLight(float ambient, float diffuse, float specular,
	float constant, float linear, float quadratic,
	lm::FVec3 color)
{
	if (pointLights.size() >= g_nbMaxLight)
		return nullptr;

	PointLight* object = new PointLight(ambient, diffuse, specular, constant, linear, quadratic, color);
	pointLights.push_back(object);

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreateDirLight(float ambient, float diffuse, float specular,
	lm::FVec3 color)
{
	if (dirLights.size() >= g_nbMaxLight)
		return nullptr;

	DirLight* object = new DirLight(ambient, diffuse, specular, color);
	dirLights.push_back(object);

	return AddGameObject(object);
}

GameObject* GameObjectManager::CreateCamera()
{
	Camera* object = new Camera();
	
	if (!currentCamera) 
	{
		currentCamera = object;
	}

	return AddGameObject(object);
}

void GameObjectManager::Remove(GameObject* object)
{
	auto it = std::find(gameObjects.begin(), gameObjects.end(), object);

	if (it != gameObjects.end())
		gameObjects.erase(it);

	auto pointsTemp = std::find(pointLights.begin(), pointLights.end(), object);

	if (pointsTemp != pointLights.end())
		pointLights.erase(pointsTemp);

	auto spotTemp = std::find(spotLights.begin(), spotLights.end(), object);

	if (spotTemp != spotLights.end())
		spotLights.erase(spotTemp);

	auto dirTemp = std::find(dirLights.begin(), dirLights.end(), object);

	if (dirTemp != dirLights.end())
		dirLights.erase(dirTemp);

}

std::vector<GameObject*> GameObjectManager::FindObjectsByName(std::string name)
{
	std::vector<GameObject*> namedObjects;

	for (auto& gameObject : gameObjects)
		if (gameObject->GetName() == name)
			namedObjects.push_back(gameObject);

	return namedObjects;
}

GameObject* GameObjectManager::FindObjectByName(std::string name)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetName() == name)
		{
			return gameObjects[i];
		}
	}
	return nullptr;
}

GameObject* GameObjectManager::FindObjectById(int id)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetId() == id)
		{
			return gameObjects[i];
		}
	}
	return nullptr;
}

Camera* GameObjectManager::GetCurrentCamera()
{
	return currentCamera;
}

void GameObjectManager::SetCurrentCamera(Camera* camera)
{
	currentCamera = camera;
}

void GameObjectManager::SendLightsToShader()
{
	for (int i = 0; i < dirLights.size(); i++)
	{
		dirLights[i]->SendToShader(i, g_dirLightShaderName);
	}
	for (int i = 0; i < pointLights.size(); i++)
	{
		pointLights[i]->SendToShader(i, g_pointLightShaderName);
	}
	for (int i = 0; i < spotLights.size(); i++)
	{
		spotLights[i]->SendToShader(i, g_spotLightShaderName);
	}
}

int GameObjectManager::GetDirLightSize()
{
	int nbLight = 0;
	for (DirLight* l : dirLights)
	{
		if (l->IsActiveForReal())
		{
			nbLight++;
		}
	}
	return nbLight;
}

int GameObjectManager::GetPointLightSize()
{
	int nbLight = 0;
	for (PointLight* l : pointLights)
	{
		if (l->IsActiveForReal())
		{
			nbLight++;
		}
	}
	return nbLight;
}

int GameObjectManager::GetSpotLightSize()
{
	int nbLight = 0;
	for (SpotLight* l : spotLights)
	{
		if (l->IsActiveForReal())
		{
			nbLight++;
		}
	}
	return nbLight;
}

void GameObjectManager::SetFocusedGameObject(GameObject* obj)
{
	focusedObject = obj;
}

GameObject* GameObjectManager::GetFocusedGameObject()
{
	return focusedObject;
}

GameObject* GameObjectManager::AddGameObject(GameObject* object)
{
	gameObjects.push_back(object);
	SetFocusedGameObject(object);
	return object;
}