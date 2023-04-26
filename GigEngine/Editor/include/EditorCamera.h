#pragma once
#include "Camera.h"

class EditorCamera : public Camera
{
public:
	EditorCamera();
	~EditorCamera() override;

	void Update();

private:
	void ChangeSpeed();
	void Move();
	void Look();

	float speed = 2;
	float speedStep = 2;
	float speedMax = 50;
	float sensitivity = 2;

	const float maxLookAngle = 89;

	bool pressLeftShift = false;
	bool pressRightShift = false;
};
