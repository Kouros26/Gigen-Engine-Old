#pragma once
#include "UIElement.h"
#include "Shader.h"
#include <vector>

class UIManager
{
public:
	UIManager();
	~UIManager();

	static void Init();
	static void AddImageElement();
	static void AddTextElement();
	static void DrawUI();

	static int GetUISize();
	static int GetWorldSize();

	static UIElement* GetUIElement(unsigned int i);
	static UIElement* GetWorldElement(unsigned int i);

	static void SetFocusedElement(UIElement* elem);
	static UIElement* GetFocusedElement();

	static void RemoveElement(UIElement* elem);
	static UIElement* CreateUIElement(UIElement* elem);

	static UIElement* AddToWorldElements(UIElement* elem);
	static UIElement* AddToUIElements(UIElement* elem);

private:
	inline static unsigned int PROJECTIONLocation;
	inline static unsigned int COLORLocation;
	inline static unsigned int IMAGELocation;
	inline static unsigned int ORTHOLocation;
	inline static unsigned int MODELLocation;
	inline static unsigned int ISWORLDLocation;
	inline static ShaderProgram shaderProgram;

	inline static UIElement* focusedElement = nullptr;
	inline static std::vector<UIElement*> elements;
	inline static std::vector<UIElement*> worldElements;
};
