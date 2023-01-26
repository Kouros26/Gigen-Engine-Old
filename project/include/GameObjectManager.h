#pragma once
#include "Camera.h"

class Model;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	static void Init();
	static unsigned int GetSize();
	static GameObject* GetGameObject(int i);
	static void Cleanup();
	static void AddGameObject(GameObject* object);
	static std::vector<GameObject*> FindObjectsByName(std::string name);
	static Camera* GetCurrentCamera();
	static void SetCurrentCamera(Camera* camera);
	static void InitSkyBox(Model* model);
	static Model* GetSkyBox();

private:
	inline static Camera* editorCamera;
	inline static Camera* currentCamera;
	inline static Model* SkyBox;
	inline static std::vector<GameObject*> gameObjects;
};
