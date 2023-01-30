#pragma once
#include "Vec3/Vec3.h"
#include "Mat4/Mat4.h"

class Transform
{
public:
	Transform();
	~Transform();

	void SetPosition(lm::vec3 pos);
	void SetRotation(lm::vec3 rot);
	void SetScale(lm::vec3 scl);

	lm::vec3 GetPosition() const;
	lm::vec3 GetScale() const;
	lm::vec3 GetRotation() const;

	void AddScale(lm::vec3 scl);
	void AddRotation(lm::vec3 rot);
	void AddPosition(lm::vec3 pos);

	lm::vec3 GetFront();
	lm::vec3 GetUp();
	lm::vec3 GetRight();

	lm::mat4 GetMatrix();

private:
	void UpdateMatrix();
	void ClampRotation();

	lm::vec3 scale = lm::vec3(1);
	lm::vec3 position;
	lm::vec3 rotation;
	lm::mat4 matrix;
};