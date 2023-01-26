#pragma once
#include "Application.h"

const std::string DEFAULT_TEXTURE_PATH = "Assets/textures/defaultTexture.jpg";

class Texture
{
public:
	Texture();
	Texture(std::string filePath);
	~Texture();

	std::string filePath;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	VkImageView textureImageView;
	VkSampler textureSampler;

private:
	void CreateTextureImage();
	void CreateTextureImageView();
	void CreateTextureSampler();

	void Texture::CopyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void Texture::TransitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
};