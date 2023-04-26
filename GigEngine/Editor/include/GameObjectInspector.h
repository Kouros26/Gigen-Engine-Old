#pragma once
#include "Displayable.h"
#include <string>

class GameObject;
class Camera;

class GameObjectInspector : public Displayable
{
public:

	GameObjectInspector();
	~GameObjectInspector() override;

	void Draw() override;

private:
	void DrawGameObject();

	void DrawTransform(GameObject* pObject) const;
	void DrawModel(GameObject* pObject) const;
	void DrawTexture(GameObject* pObject) const;

	void DrawSpecials(GameObject* pObject) const;
	void DrawComponents(GameObject* pObject);

	void DrawLight(GameObject* pObject) const;
	void DrawCamera(Camera* pObject) const;

	static std::string GetFilePathFromExplorer(const char* filter);
};
