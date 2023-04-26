#include "Material.h"
#include "Application.h"

Material::Material()
{
}

Material::~Material()
{
}

Material::Material(lm::FVec3 pDiff, lm::FVec3 pAmb, lm::FVec3 pSpec, float pShini)
	:shininess(pShini)
{
	for (int i = 0; i < 3; i++)
	{
		diffuse[i] = pDiff[i];
		specular[i] = pSpec[i];
		ambient[i] = pAmb[i];
	}
}

void Material::SendToShader()
{
	ShaderProgram& shader = Application::GetMainShader();

	shader.SetVec3(diffuse, "material.diffuse");
	shader.SetVec3(ambient, "material.ambient");
	shader.SetVec3(specular, "material.specular");
	shader.SetFloat(shininess, "material.shininess");
}

void Material::SendDefaultMaterial()
{
	ShaderProgram& shader = Application::GetMainShader();

	float base[3]{ 1, 1, 1 };
	float baseShini = 1.0f;

	shader.SetVec3(base, "material.diffuse");
	shader.SetVec3(base, "material.ambient");
	shader.SetVec3(base, "material.specular");
	shader.SetFloat(baseShini, "material.shininess");
}

void Material::SetDiffuse(lm::FVec3 pVec)
{
	for (int i = 0; i < 3; i++)
	{
		diffuse[i] = pVec[i];
	}
}

void Material::SetAmbient(lm::FVec3 pVec)
{
	for (int i = 0; i < 3; i++)
	{
		ambient[i] = pVec[i];
	}
}

void Material::SetSpecular(lm::FVec3 pVec)
{
	for (int i = 0; i < 3; i++)
	{
		specular[i] = pVec[i];
	}
}

void Material::SetShininess(float pShini)
{
	shininess = pShini;
}