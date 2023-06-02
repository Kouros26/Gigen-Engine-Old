#pragma once
#include <string>
#include "AudioSource.h"
#include "Camera.h"
#include "Light.h"
#include "UIElement.h"

namespace formatting
{
	const std::string skyboxTag("B");
	const std::string typeTag("*");
	const std::string lightValueTag(".");
	const std::string cameraValueTag("-");
	const std::string nameTag("N");
	const std::string transformTag("W");
	const std::string rigidBodyTag("R");
	const std::string parentTag("P");
	const std::string componentTag("C");
	const std::string modelTag("M");
	const std::string textureTag("T");
}

struct ProcessedObject // describes the gameObject that is currently handled
{
	inline static std::string type;
	inline static std::string name;
	inline static std::string otherValues;
	inline static std::string transform;
	inline static std::string rigidBody;
	inline static std::string parent;
	inline static std::string components;
	inline static std::string model;
	inline static std::string texture;

	inline static unsigned int componentSize;

	static void Clear();
};

class Scene
{
public:

	void SaveScene(const std::string& pSceneName);
	void LoadScene(const std::string& pSceneName);
	void ReloadScene(const std::string& pSceneName);

	std::string& GetCurrentSceneName();
	static Scene& GetInstance();

private:

	void GetValues(GameObject* pGameObject);
	void GetAudioValues(AudioSource* pAudioSource) const;
	void GetLightValues(DirLight* pGameObject) const;
	void GetUIValues(UIElement* pUI) const;
	void GetCameraValues(const Camera* pGameObject) const;
	bool IsLight(const std::string& pType);

	GameObject* ProcessTypeOfGameObject(const std::string& pLine);
	void ProcessLightData(const std::string& pLine, GameObject* pOutGameObject);
	void ProcessCameraData(const std::string& pLine, Camera* pOutGameObject);
	void ProcessTransform(const std::string& pLine, GameObject* pOutGameObject);
	void ProcessRigidBody(const std::string& pLine, GameObject* pOutGameObject);
	void ProcessComponents(const std::string& pLine, GameObject* pOutGameObject);
	void LoadSound(const std::vector<std::string>& pStrings, GameObject* pOutGameObject, int i) const;

	[[nodiscard]] std::string VecToString(const float pFirst, const float pSecond, const float pThird) const;
	[[nodiscard]] std::string VecToString(const lm::FVec3& pVec) const;
	std::vector<std::string> SplitString(const std::string& pString, char delimiter = ' ');

	std::string sceneFolder = "Scenes/";
	std::string currentScene = "default.chad";

	std::vector<std::pair<std::string, std::string>> parentChildMemory;
};
