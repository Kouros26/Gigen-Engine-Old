#pragma once
#include "Shader.h"
#include "GameObject.h"

class ShaderProgram;

const char* const g_SkyboxModelPath = "Engine/Models/Skybox/cube.obj";
const char* const g_SkyboxTexturePath = "Engine/Textures/Skybox/default.png";

class Skybox : public GameObject
{
public:
	Skybox();
	~Skybox();

	void Draw();

	lm::FVec3& GetColor();
	void SetColor(lm::FVec3 col);

private:
	lm::FVec3 color = lm::FVec3(1);
	unsigned int viewProjLocation;
	unsigned int ColorLocation;
	unsigned int ModelLocation;
	ShaderProgram shaderProgram;
};
