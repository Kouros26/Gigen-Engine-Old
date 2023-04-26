#include "Texture.h"
#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
#include <iostream>
#include "IResource.h"
#include "Renderer.h"

using namespace GigRenderer;

Texture::Texture(std::string const& pFilePath)
    :IResource(pFilePath)
{
    texture = 0;
}

Texture::~Texture()
{
    RENDERER.DeleteTexture(texture);
}

void Texture::Load()
{
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        RENDERER.LoadTexture(texture, width, height, data);
        valid = true;
    }
    else
    {
        std::cout << "Failed to load texture : " << filePath << std::endl;
    }
    stbi_image_free(data);
}

void Texture::Bind()
{
    RENDERER.BindTexture(RD_TEXTURE_2D, texture);
}

void Texture::UnBind()
{
    RENDERER.BindTexture(RD_TEXTURE_2D, 0);
}

bool Texture::isValid()
{
    return valid;
}

void Texture::Init()
{
    Load();
}