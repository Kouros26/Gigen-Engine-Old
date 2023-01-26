#pragma once
#include "Component.h"
#include "Texture.h"
#include "Mesh.h"

class Model : public Component
{
public:
	Model(GameObject* gameObject);
	virtual ~Model() override;

	Mesh mesh;
	Texture* texture;
};