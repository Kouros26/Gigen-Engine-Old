#pragma once
#include "UIElement.h"
#include <string>

class Font;

class UIText : public UIElement
{
public:
	UIText();
	~UIText();

	void SetFont(const std::string& path);
	void SetText(const std::string& t);
	std::string& GetText();
	void Draw() override;

private:
	std::string text = "Hello world!";
	Font* font = nullptr;
};
