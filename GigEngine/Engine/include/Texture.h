#pragma once
#include "IResource.h"

const char* const g_defaultTexturePath = "Engine/Textures/default.png";
const char* const g_defaultTexturePath2 = "Engine/Textures/default2.png";

class Texture : public IResource
{
public:
	Texture(std::string const& pFilePath);
	~Texture();

	void Bind();
	static void UnBind();
	bool isValid();

	void Init() override;

private:
	unsigned int texture;
	void Load();

	bool valid = false;
};