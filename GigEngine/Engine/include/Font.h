#pragma once
#include "IResource.h"
#include "Vec2/FVec2.hpp"
#include <map>

const char* const g_defaultFontPath = "Engine/Fonts/Ruda-Bold.ttf";

struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	lm::FVec2   Size;       // Size of glyph
	lm::FVec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

class Font : public IResource
{
public:
	Font(std::string const& pFilePath);
	~Font();

	void Init() override;

	Character& GetCharacter(char c);
	void AddCharacter(std::pair<char, Character> c);

	unsigned int& GetVAO();
	unsigned int& GetVBO();
private:
	unsigned int VAO, VBO;
	std::map<char, Character> characters;
};