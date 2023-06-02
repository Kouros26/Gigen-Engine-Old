#include "RectTransform.h"

RectTransform::RectTransform()
{
	SetPosition({ 0,0 });
	matrix = lm::FMat4::Transform({ position.x, position.y, 0 }, { 0 }, { size.x, size.y, 0 });
}

RectTransform::~RectTransform()
{
}

void RectTransform::SetPosition(lm::FVec2 vec)
{
	hasChanged = true;

	position = vec;
}

void RectTransform::SetWidth(float w)
{
	size.x = w;
}

void RectTransform::SetHeight(float h)
{
	size.y = h;
}

void RectTransform::SetSize(lm::FVec2 vec)
{
	size = vec;
}

void RectTransform::SetAnchorX(AnchorX anchor)
{
	anchorX = anchor;
}

void RectTransform::SetAnchorY(AnchorY anchor)
{
	anchorY = anchor;
}

AnchorX& RectTransform::GetAnchorX()
{
	return anchorX;
}

AnchorY& RectTransform::GetAnchorY()
{
	return anchorY;
}

lm::FVec2 RectTransform::GetPosition()
{
	return position;
}

lm::FVec2 RectTransform::GetSize()
{
	return size;
}

lm::FMat4& RectTransform::getMatrix()
{
	if (hasChanged)
	{
		matrix = lm::FMat4::Transform({ position.x, position.y, 0 }, { 0 }, { size.x, size.y, 0 });
		hasChanged = false;
	}

	return matrix;
}