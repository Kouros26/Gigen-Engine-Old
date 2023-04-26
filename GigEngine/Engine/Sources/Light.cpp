#include "Light.h"
#include "Application.h"
#include <string>

DirLight::DirLight(float ambient, float diffuse, float specular, lm::FVec3 color)
	:ambient(ambient), diffuse(diffuse), specular(specular)
{
	this->color[0] = color.x;
	this->color[1] = color.y;
	this->color[2] = color.z;
}

void DirLight::SendToShader(const int& pos, const std::string& shaderName)
{
	if (!IsActiveForReal())
	{
		return;
	}
	std::string str = shaderName + "[" + std::to_string(pos) + "].";
	std::string temp = str;

	lm::FVec3 dir = GetTransform().GetFront();
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
}

float* DirLight::GetColor()
{
	return color;
}

float DirLight::GetAmbient()
{
	return ambient;
}

float DirLight::GetDiffuse()
{
	return diffuse;
}

float DirLight::GetSpecular()
{
	return specular;
}

void DirLight::SetColor(lm::FVec3 pColor)
{
	for (int i = 0; i < 3; i++)
	{
		color[i] = pColor[i];
	}
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

PointLight::PointLight(float ambient, float diffuse, float specular, float constant, float linear, float quadratic, lm::FVec3 color)
	:DirLight(ambient, diffuse, specular, color), constant(constant), linear(linear), quadratic(quadratic)
{
}

void PointLight::SendToShader(const int& pos, const std::string& shaderName)
{
	if (!IsActiveForReal())
	{
		return;
	}
	DirLight::SendToShader(pos, shaderName);

	std::string str = shaderName + "[" + std::to_string(pos) + "].";
	std::string temp = str;

	lm::FVec3 posi = GetTransform().GetWorldPosition();
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

float PointLight::GetConstant()
{
	return constant;
}

float PointLight::GetLinear()
{
	return linear;
}

float PointLight::GetQuadratic()
{
	return quadratic;
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

SpotLight::SpotLight(float ambient, float diffuse, float specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff, lm::FVec3 color)
	:PointLight(ambient, diffuse, specular, constant, linear, quadratic, color), cutOff(cutOff), outerCutOff(outerCutOff)
{
}

void SpotLight::SendToShader(const int& pos, const std::string& shaderName)
{
	if (!IsActiveForReal())
	{
		return;
	}
	PointLight::SendToShader(pos, shaderName);

	std::string str = shaderName + "[" + std::to_string(pos) + "].";
	std::string temp = str;

	ShaderProgram& shader = Application::GetMainShader();
	shader.SetFloat(cutOff, (str.append(g_cutOffShaderName)).c_str());
	str = temp;
	shader.SetFloat(outerCutOff, (str.append(g_outerCutOffShaderName)).c_str());
}

float SpotLight::GetCutOff()
{
	return cutOff;
}

float SpotLight::GetOuterCutOff()
{
	return outerCutOff;
}

void SpotLight::SetCutOff(float pCutOff)
{
	cutOff = pCutOff;
}

void SpotLight::SetOuterCutOff(float pOuterCutOff)
{
	outerCutOff = pOuterCutOff;
}