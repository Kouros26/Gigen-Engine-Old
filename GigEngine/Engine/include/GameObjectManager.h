#pragma once
#include <vector>
#include <string>
#include "Vec3/FVec3.hpp"
#include "Mat4/FMat4.hpp"
#include "Skybox.h"

class GameObject;
class Camera;
class DirLight;
class SpotLight;
class PointLight;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	static unsigned int GetSize();
	static GameObject*& GetGameObject(int i);
	static void Cleanup();

	static GameObject* CreateGameObject();
	static GameObject* CreateGameObject(const std::string& name);
	static GameObject* CreateGameObject(const std::string& name, const lm::FVec3& position, const lm::FVec3& rotation, const lm::FVec3& scale);
	static GameObject* CreateGameObject(const lm::FVec3& position, const lm::FVec3& rotation, const lm::FVec3& scale);

	static GameObject* CreateGameObject(const GameObject& other);
	static GameObject* CreateGameObject(GameObject&& other) noexcept = delete;
	static GameObject* CreateGameObject(const GameObject* other);
	static GameObject* CreateGameObject(GameObject*&& other) noexcept = delete;

	static void UpdateLightSpaceMatrix(Camera* cam);

	//rule of 5
	GameObject& operator=(const GameObject& other) const;
	GameObject& operator=(GameObject&& other) noexcept;

	static GameObject* CreateSpotLight(float ambient = 0.0f, float diffuse = 0.5f, float specular = 0.5f,
		float constant = 0.1f, float linear = 0.02f, float quadratic = 0.01f,
		float cutOff = 10, float outerCutOff = 25,
		const lm::FVec3& color = lm::FVec3(1));

	static GameObject* CreatePointLight(float ambient = 0.0f, float diffuse = 0.5f, float specular = 0.5f,
		float constant = 0.1f, float linear = 0.02f, float quadratic = 0.01f,
		const lm::FVec3& color = lm::FVec3(1));

	static GameObject* CreateDirLight(float ambient = 0.0f, float diffuse = 0.5f, float specular = 0.5f,
		const lm::FVec3& color = lm::FVec3(1));

	static GameObject* CreateCamera();

	static Camera* GetCurrentCamera();
	static void SetCurrentCamera(Camera* camera);

	static void CreateSkyBox();
	static Skybox* GetSkyBox();

	static void SendLightsToShader();
	static int GetDirLightSize();
	static int GetPointLightSize();
	static int GetSpotLightSize();
	static void SetFocusedGameObject(GameObject* obj);
	static GameObject* GetFocusedGameObject();
	static void RemoveGameObject(GameObject* object);

	static std::vector<GameObject*> FindObjectsByName(const std::string& name);
	static GameObject* FindObjectByName(const std::string& name);
	static GameObject* FindObjectById(unsigned int id);

	static lm::FMat4& GetDirLightSpaceMatrix();

private:
	static GameObject* AddGameObject(GameObject* object);

	inline static lm::FMat4 lightSpaceMatrix;

	inline static Skybox* skybox = nullptr;
	inline static Camera* currentCamera;
	inline static std::vector<GameObject*> gameObjects;

	inline static std::vector<DirLight*> dirLights;
	inline static std::vector<SpotLight*> spotLights;
	inline static std::vector<PointLight*> pointLights;
	inline static GameObject* focusedObject;
};
