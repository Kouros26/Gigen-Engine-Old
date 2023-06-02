#pragma once
#include "GameObject.h"
#include "Vec3/FVec3.hpp"

constexpr int g_nbMaxLight = 50;

const char* const g_dirLightShaderName = "dirLights";
const char* const g_pointLightShaderName = "pointLights";
const char* const g_spotLightShaderName = "spotLights";

const char* const g_colorShaderName = "color";
const char* const g_directionShaderName = "direction";
const char* const g_positionShaderName = "position";

const char* const g_ambientShaderName = "ambient";
const char* const g_diffuseShaderName = "diffuse";
const char* const g_specularShaderName = "specular";

const char* const g_constantShaderName = "constant";
const char* const g_linearShaderName = "linear";
const char* const g_quadraticShaderName = "quadratic";

const char* const g_cutOffShaderName = "cutOff";
const char* const g_outerCutOffShaderName = "outerCutOff";

class DirLight : public GameObject
{
public:
	DirLight(float ambient = 0.5f, float diffuse = 0.5f, float specular = 0.5f, const lm::FVec3& color = lm::FVec3(1));

	virtual void SendToShader(const int& pos, int type);

	float* GetColor();
	[[nodiscard]] float GetAmbient() const;
	[[nodiscard]] float GetDiffuse() const;
	[[nodiscard]] float GetSpecular() const;
	virtual std::string GetType() override;

	void SetColor(const lm::FVec3& pColor);
	void SetAmbient(float pAmbient);
	void SetDiffuse(float pDiffuse);
	void SetSpecular(float pSpecular);

private:
	float direction[3]{};
	float color[3]{};

	float ambient;
	float diffuse;
	float specular;
};

class PointLight : public DirLight
{
public:
	PointLight(float ambient = 0.5f, float diffuse = 0.5f, float specular = 0.5f,
		float constant = 0.1f, float linear = 0.02f, float quadratic = 0.01f,
		const lm::FVec3& color = lm::FVec3(1));

	virtual void SendToShader(const int& pos, int type) override;

	[[nodiscard]] float GetConstant() const;
	[[nodiscard]] float GetLinear() const;
	[[nodiscard]] float GetQuadratic() const;
	virtual std::string GetType() override;

	void SetConstant(float pConstant);
	void SetLinear(float pLinear);
	void SetQuadratic(float pQuadratic);

private:
	float position[3]{};

	float constant;
	float linear;
	float quadratic;
};

class SpotLight : public PointLight
{
public:
	SpotLight(float ambient = 0.5f, float diffuse = 0.5f, float specular = 0.5f,
		float constant = 0.1f, float linear = 0.02f, float quadratic = 0.01f,
		float cutOff = 10, float outerCutOff = 25,
		const lm::FVec3& color = lm::FVec3(1));

	virtual void SendToShader(const int& pos, int type) override;

	[[nodiscard]] float GetCutOff() const;
	[[nodiscard]] float GetOuterCutOff() const;
	virtual std::string GetType() override;

	void SetCutOff(float pCutOff);
	void SetOuterCutOff(float pOuterCutOff);

private:
	float cutOff;
	float outerCutOff;
};