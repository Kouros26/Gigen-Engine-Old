#include "GameObjectManager.h"
#include "Model.h"
#include "FreeCam.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Init()
{
	editorCamera = new Camera();
	editorCamera->AddNewComponent<FreeCam>();
	SetCurrentCamera(editorCamera);
}

unsigned int GameObjectManager::GetSize()
{
	return (unsigned int)gameObjects.size();
}

GameObject* GameObjectManager::GetGameObject(int i)
{
	return gameObjects[i];
}

void GameObjectManager::Cleanup()
{
	for (size_t i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i])
			delete gameObjects[i];
	}

	if (SkyBox)
		delete SkyBox;

	if (editorCamera)
		delete editorCamera;
}

void GameObjectManager::AddGameObject(GameObject* object)
{
	if (std::find(gameObjects.begin(), gameObjects.end(), object) == gameObjects.end())
		gameObjects.push_back(object);
}

std::vector<GameObject*> GameObjectManager::FindObjectsByName(std::string name)
{
	std::vector<GameObject*> namedObjects;
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i]->GetName() == name) 
		{
			namedObjects.push_back(gameObjects[i]);
		}
	}
	return namedObjects;
}

Camera* GameObjectManager::GetCurrentCamera()
{
	return currentCamera;
}

void GameObjectManager::SetCurrentCamera(Camera* camera)
{
	currentCamera = camera;
}

void GameObjectManager::InitSkyBox(Model* model)
{
	SkyBox = model;
}

Model* GameObjectManager::GetSkyBox()
{
	return SkyBox;
}
