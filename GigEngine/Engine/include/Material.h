#pragma once

namespace lm
{
	class FVec3;
}

class Material
{
public:
	Material();
	Material(lm::FVec3 pDiff, lm::FVec3 pAmb, lm::FVec3 pSpec, float pShini);
	~Material();

	void SendToShader();
	static void SendDefaultMaterial();

	void SetDiffuse(lm::FVec3 pVec);
	void SetAmbient(lm::FVec3 pVec);
	void SetSpecular(lm::FVec3 pVec);
	void SetShininess(float pShini);

private:
	float diffuse[3];
	float ambient[3];
	float specular[3];

	float shininess = 1.0f;
};