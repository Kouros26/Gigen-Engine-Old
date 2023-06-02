#include "UIImage.h"
#include "Renderer.h"
#include "Application.h"
#include "ShadowMapping.h"
#include "ResourceManager.h"

using namespace GigRenderer;

UIImage::UIImage() : UIElement("Image")
{
	texture = ResourceManager::Get<Texture>(g_defaultTexturePath);
	SetIsImage(1);
	GetRectTransform().SetSize({ 100 });
	RENDERER.LoadUIImage(this);
}

UIImage::~UIImage()
{
}

unsigned int& UIImage::GetVAO()
{
	return VAO;
}

unsigned int& UIImage::GetVBO()
{
	return VBO;
}

void UIImage::SetTexture(const std::string& path)
{
	texture = ResourceManager::Get<Texture>(path);
}

void UIImage::Draw()
{
	GigRenderer::RENDERER.BindVertexArray(VAO);

	const lm::FVec2 size = GetRectTransform().GetSize();
	// iterate through all characters
	std::string::const_iterator c;

	float xpos = GetRectTransform().GetPosition().x;
	float ypos = GetRectTransform().GetPosition().y;

	switch (GetRectTransform().GetAnchorX())
	{
	case AnchorX::CENTER:
		xpos += (Application::GetWindow().GetVPWidth() / 2) - (size.x / 2);
		break;
	case AnchorX::RIGHT:
		xpos += Application::GetWindow().GetVPWidth() - size.x;
		break;
	}

	switch (GetRectTransform().GetAnchorY())
	{
	case AnchorY::CENTER:
		ypos += (Application::GetWindow().GetVPHeight() / 2) - (size.y / 2);
		break;
	case AnchorY::UP:
		ypos += Application::GetWindow().GetVPHeight() - size.y;
		break;
	}

	const float w = size.x;
	const float h = size.y;
	// update VBO for each character
	float vertices[6][4] = {
		{ xpos,     ypos + h,   0.0f, 0.0f },
		{ xpos,     ypos,       0.0f, 1.0f },
		{ xpos + w, ypos,       1.0f, 1.0f },

		{ xpos,     ypos + h,   0.0f, 0.0f },
		{ xpos + w, ypos,       1.0f, 1.0f },
		{ xpos + w, ypos + h,   1.0f, 0.0f }
	};
	// render glyph texture over quad

	texture->Bind();
	// update content of VBO memory
	RENDERER.BindBuffer(GigRenderer::BufferType::VERTEX, VBO);
	RENDERER.BufferSubData(GigRenderer::BufferType::VERTEX, 0, sizeof(vertices), vertices);
	RENDERER.BindBuffer(GigRenderer::BufferType::VERTEX, 0);

	RENDERER.DrawArray(GL_TRIANGLES, 0, 6);

	RENDERER.BindVertexArray(0);
	RENDERER.BindTexture(GL_TEXTURE_2D, 0, RD_TEXTURE0);
}