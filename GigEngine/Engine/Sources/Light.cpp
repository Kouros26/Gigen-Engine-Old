#include "Light.h"
#include "Application.h"
#include <string>

DirLight::DirLight(float ambient, float diffuse, float specular, const lm::FVec3& color)
	: GameObject("Light"), ambient(ambient), diffuse(diffuse), specular(specular)
{
	this->color[0] = color.x;
	this->color[1] = color.y;
	this->color[2] = color.z;
}

void DirLight::SendToShader(const int& pos, int type)
{
	if (!IsActive())
		return;

	std::string str = "lights[" + std::to_string(pos) + "].";
	const std::string temp = str;

	const lm::FVec3 dir = GetTransform().GetFront();
	direction[0] = dir.x;
	direction[1] = dir.y;
	direction[2] = dir.z;

	ShaderProgram& shader = Application::GetMainShader();
	shader.SetVec3(direction, (str.append(g_directionShaderName)).c_str());
	str = temp;
	shader.SetVec3(color, (str.append(g_colorShaderName)).c_str());
	str = temp;
	shader.SetFloat(ambient, (str.append(g_ambientShaderName)).c_str());
	str = temp;
	shader.SetFloat(diffuse, (str.append(g_diffuseShaderName)).c_str());
	str = temp;
	shader.SetFloat(specular, (str.append(g_specularShaderName)).c_str());
	str = temp;
	shader.SetInt(type, (str.append("type")).c_str());
}

float* DirLight::GetColor()
{
	return color;
}

float DirLight::GetAmbient() const
{
	return ambient;
}

float DirLight::GetDiffuse() const
{
	return diffuse;
}

float DirLight::GetSpecular() const
{
	return specular;
}

void DirLight::SetColor(const lm::FVec3& pColor)
{
	for (int i = 0; i < 3; i++)
		color[i] = pColor[i];
}

void DirLight::SetAmbient(float pAmbient)
{
	ambient = pAmbient;
}

void DirLight::SetDiffuse(float pDiffuse)
{
	diffuse = pDiffuse;
}

void DirLight::SetSpecular(float pSpecular)
{
	specular = pSpecular;
}

std::string DirLight::GetType()
{
	const std::string type(typeid(this).name());
	return type.substr(6, type.size() - 16);
}

PointLight::PointLight(float ambient, float diffuse, float specular, float constant, float linear, float quadratic,
                       const lm::FVec3& color)
	:DirLight(ambient, diffuse, specular, color), constant(constant), linear(linear), quadratic(quadratic)
{
}

void PointLight::SendToShader(const int& pos, int type)
{
	if (!IsActive())
		return;

	DirLight::SendToShader(pos, type);

	std::string str = "lights[" + std::to_string(pos) + "].";
	const std::string temp = str;

	const lm::FVec3 posi = GetTransform().GetWorldPosition();
	position[0] = posi.x;
	position[1] = posi.y;
	position[2] = posi.z;

	ShaderProgram& shader = Application::GetMainShader();
	shader.SetVec3(position, (str.append(g_positionShaderName)).c_str());
	str = temp;
	shader.SetFloat(constant, (str.append(g_constantShaderName)).c_str());
	str = temp;
	shader.SetFloat(linear, (str.append(g_linearShaderName)).c_str());
	str = temp;
	shader.SetFloat(quadratic, (str.append(g_quadraticShaderName)).c_str());
}

float PointLight::GetConstant() const
{
	return constant;
}

float PointLight::GetLinear() const
{
	return linear;
}

float PointLight::GetQuadratic() const
{
	return quadratic;
}

std::string PointLight::GetType()
{
	const std::string type(typeid(this).name());
	return type.substr(6, type.size() - 16);
}

void PointLight::SetConstant(float pConstant)
{
	constant = pConstant;
}

void PointLight::SetLinear(float pLinear)
{
	linear = pLinear;
}

void PointLight::SetQuadratic(float pQuadratic)
{
	quadratic = pQuadratic;
}

SpotLight::SpotLight(float ambient, float diffuse, float specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff,
                     const lm::FVec3& color)
	:PointLight(ambient, diffuse, specular, constant, linear, quadratic, color), cutOff(cutOff), outerCutOff(outerCutOff)
{
}

void SpotLight::SendToShader(const int& pos, int type)
{
	if (!IsActive())
		return;

	PointLight::SendToShader(pos, type);

	std::string str = "lights[" + std::to_string(pos) + "].";
	const std::string temp = str;

	ShaderProgram& shader = Application::GetMainShader();
	shader.SetFloat(cutOff, (str.append(g_cutOffShaderName)).c_str());
	str = temp;
	shader.SetFloat(outerCutOff, (str.append(g_outerCutOffShaderName)).c_str());
}

float SpotLight::GetCutOff() const
{
	return cutOff;
}

float SpotLight::GetOuterCutOff() const
{
	return outerCutOff;
}

std::string SpotLight::GetType()
{
	const std::string type(typeid(this).name());
	return type.substr(6, type.size() - 16);
}

void SpotLight::SetCutOff(float pCutOff)
{
	cutOff = pCutOff;
}

void SpotLight::SetOuterCutOff(float pOuterCutOff)
{
	outerCutOff = pOuterCutOff;
}