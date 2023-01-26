#pragma once
#include "Component.h"

class FreeCam : public Component
{
public:
	FreeCam(GameObject* gameObject);
	~FreeCam();

	virtual void Update() override;

private:
	float speed = 2;
	float speedStep = 2;
	float speedMax = 50;
	float sensitivity = 2;

	float maxLookAngle = 80;

	bool pressLeftShift = false;
	bool pressRightShift = false;
};
