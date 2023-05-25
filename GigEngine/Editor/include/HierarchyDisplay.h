#pragma once
#include "Displayable.h"

class GameObject;
class UIElement;

class HierarchyDisplay : public Displayable
{
public:

	HierarchyDisplay();
	~HierarchyDisplay() override;

	void Draw() override;

private:

	void DisplayHierarchy() const;
	void DisplaySkybox() const;
	void DisplayUI() const;
	void DisplayUIElement(UIElement& element) const;

	void CreatePopUp() const;

	void DisplayGameObject(GameObject& obj, bool isChild) const;
	void GameObjectClicked(GameObject& obj) const;
	void GameObjectPopUp(GameObject& obj) const;
};