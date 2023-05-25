#pragma once
#include "Object.h"
#include "RectTransform.h"
#include "Transform.h"

class UIElement : public Object
{
public:
	UIElement();
	UIElement(const std::string& name);
	UIElement(UIElement& other);
	virtual ~UIElement() override;

	virtual void Draw();

	void SetColor(lm::FVec3 c);

	int& GetIsImage();
	void SetIsImage(int n);

	bool GetIsWorld() const;
	void SetIsWorld(bool b);

	lm::FVec3& GetColor();
	RectTransform& GetRectTransform();
	Transform& GetTransform();
private:
	bool isWorld = false;
	int isImage = 0;
	lm::FVec3 color = lm::FVec3(1);
	RectTransform rectTransform;
	Transform transform;
};
