#pragma once
#include "Shader.h"
#include "GameObject.h"

class ShaderProgram;

const char* const g_SkyboxModelPath = "Resources/Models/Skybox/cube.obj";
const char* const g_SkyboxTexturePath = "Resources/Textures/Skybox/default.png";

class Skybox : GameObject
{
public:
	Skybox();
	~Skybox();

	void Draw();

private:
	int viewProjLocation;
	int ModelLocation;
	ShaderProgram shaderProgram;
};
