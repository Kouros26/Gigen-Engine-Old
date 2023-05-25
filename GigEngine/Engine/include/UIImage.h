#pragma once
#include "UIElement.h"
#include "Texture.h"

const char* const g_defaultPlanePath = "Engine/Models/UI/Image.obj";

class UIImage : public UIElement
{
public:
	UIImage();
	~UIImage();

	unsigned int& GetVAO();
	unsigned int& GetVBO();

	virtual void SetTexture(const std::string& path);
	virtual void Draw() override;

private:

	unsigned int VAO{}, VBO{};
	Texture* texture = nullptr;
};
