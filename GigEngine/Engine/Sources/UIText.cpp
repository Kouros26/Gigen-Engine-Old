#include "UIText.h"
#include "Font.h"
#include "Application.h"
#include "ResourceManager.h"
#include "Renderer.h"

using namespace GigRenderer;

UIText::UIText() : UIElement("Text")
{
	font = ResourceManager::Get<Font>(g_defaultFontPath);
	GetRectTransform().SetSize({ 1 });
}

UIText::~UIText()
{
}

void UIText::SetFont(const std::string& path)
{
	font = ResourceManager::Get<Font>(path);
}

std::string& UIText::GetText()
{
	return text;
}

void UIText::SetText(const std::string& t)
{
	text = t;
}

void UIText::Draw()
{
	// activate corresponding render state
	RENDERER.BindVertexArray(font->GetVAO());

	float x = GetRectTransform().GetPosition().x;
	float y = GetRectTransform().GetPosition().y;

	const lm::FVec2 size = GetRectTransform().GetSize();

	for (const char c : text)
	{
		const auto [TextureID, Size, Bearing, Advance] = font->GetCharacter(c);

		const float xpos = x + Bearing.x * size.x;
		float ypos = y - (Size.y - Bearing.y) * size.y;

		const float w = Size.x * size.x;
		const float h = Size.y * size.y;
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
		RENDERER.BindTexture(GL_TEXTURE_2D, TextureID);
		RENDERER.BindBuffer(GigRenderer::BufferType::VERTEX, font->GetVBO());
		RENDERER.BufferSubData(GigRenderer::BufferType::VERTEX, 0, sizeof(vertices), vertices);
		RENDERER.BindBuffer(GigRenderer::BufferType::VERTEX, 0);
		RENDERER.DrawArray(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (Advance >> 6) * size.x; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	RENDERER.BindVertexArray(0);
	RENDERER.BindTexture(GL_TEXTURE_2D, 0);
}