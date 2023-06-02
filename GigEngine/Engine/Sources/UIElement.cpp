#include "UIElement.h"
#include "UIManager.h"

UIElement::UIElement() : Object()
{
}

UIElement::UIElement(const std::string& pName) : Object(pName)
{
}

UIElement::UIElement(const std::string& pName, bool pIsWorld, int pIsImage, const lm::FVec3& pColor,
	const RectTransform& pRectTransform, const Transform& pTransform)
	: Object(pName),  isWorld(pIsWorld), isImage(pIsImage), color(pColor),
	  rectTransform(pRectTransform), transform(pTransform)
{
}

UIElement::UIElement(UIElement& other)
	: Object(other.GetName())
{
	transform = other.GetTransform();
	color = other.GetColor();
}

UIElement::~UIElement()
{
}

void UIElement::Draw()
{
}

void UIElement::SetColor(lm::FVec3 c)
{
	color = c;
}

int& UIElement::GetIsImage()
{
	return isImage;
}

void UIElement::SetIsImage(int n)
{
	isImage = n;
}

bool UIElement::GetIsWorld() const
{
	return isWorld;
}

void UIElement::SetIsWorld(bool b)
{
	isWorld = b;
	if (isWorld)
		UIManager::AddToWorldElements(this);

	else
		UIManager::AddToUIElements(this);
}

lm::FVec3& UIElement::GetColor()
{
	return color;
}

RectTransform& UIElement::GetRectTransform()
{
	return rectTransform;
}

Transform& UIElement::GetTransform()
{
	return transform;
}