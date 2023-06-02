#pragma once
#include "Shader.h"
#include "Mat4/FMat4.hpp"

class ShadowMapping
{
public:
	ShadowMapping();
	~ShadowMapping();

	static void Init();
	static void BeginRender();
	static void EndRender();
	static void Clear();

	static void SendLight(lm::FMat4& mat);
	static void SendModel(lm::FMat4& mat);

	static unsigned int& GetdepthMapFBO();
	static unsigned int& GetdepthMap();

private:
	inline static ShaderProgram shader;
	inline static unsigned int lightSpaceLocation;
	inline static unsigned int modelLocation;

	inline static unsigned int depthMapFBO;
	inline static unsigned int depthMap;
};
