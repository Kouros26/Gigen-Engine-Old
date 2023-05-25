#pragma once
#include "Displayable.h"
#include "Vec3/FVec3.hpp"
#include <string>

class GameObject;
class UIElement;
class UIImage;
class UIText;
class Camera;
class RigidBody;
class RectTransform;
class Transform;
class Skybox;

class GameObjectInspector : public Displayable
{
public:

	GameObjectInspector();
	~GameObjectInspector() override;

	void Draw() override;

private:
	void DrawObject() const;
	void DrawGameObject(GameObject* pObject) const;

	void DrawUIElement(UIElement* pUI) const;
	void DrawRectTransform(RectTransform* rectTransform) const;
	void DrawDropTargetImage(UIImage* pImage) const;
	void DrawUIText(UIText* pText) const;

	void DrawSkyBox(Skybox* skybox) const;

	void DrawTransform(Transform* transform) const;
	void DrawModel(GameObject* pObject) const;
	void DrawTexture(const GameObject* pObject) const;
	void DrawRigidBody(GameObject* pObject) const;
	void DrawRigidShape(RigidBody* body) const;
	void DrawRigidTransform(RigidBody* body) const;

	void DrawSpecials(GameObject* pObject) const;
	void DrawComponents(GameObject* pObject) const;

	void DrawLight(GameObject* pObject) const;
	void DrawCamera(Camera* pObject) const;

	void DrawAddComponent(GameObject* pObject) const;
	void DrawScriptsComponent(GameObject* pObject) const;
	void DrawAudiosComponent(GameObject* pObject) const;
	void DrawAnimationsComponent(GameObject* pObject) const;

	void DrawDropTarget(GameObject* pObject) const;

	void LockCalculation(float* fvec3, const lm::FVec3& original) const;
	[[nodiscard]] std::string ReadScript(const std::string& pPath) const;
};
