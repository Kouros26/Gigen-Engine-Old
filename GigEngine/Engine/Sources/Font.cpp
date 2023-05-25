#include "Font.h"
#include "Renderer.h"

Font::Font(std::string const& pFilePath) : IResource(pFilePath)
{
}

Font::~Font()
{
}

void Font::Init()
{
	GigRenderer::RENDERER.LoadFont(this);
}

Character& Font::GetCharacter(char c)
{
	return characters[c];
}

void Font::AddCharacter(std::pair<char, Character> c)
{
	characters.insert(c);
}

unsigned int& Font::GetVAO()
{
	return VAO;
}

unsigned int& Font::GetVBO()
{
	return VBO;
}