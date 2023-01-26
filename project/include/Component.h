#pragma once
#include "Watch.h"
#include "Inputs.h"
#include "GameObject.h"

class Component
{
public:
	Component(GameObject* gameObject);
	virtual ~Component();

	virtual void Update();

protected:
	GameObject* gameObject;
};

class testComponent1 : public Component
{
public:
	testComponent1(GameObject* gameObject) : Component(gameObject) {};

	virtual void Update() override {
		gameObject->transform.AddRotation(lm::vec3(20) * static_cast<float>(Time::GetDeltaTime()));
	}
};

class testComponent2 : public Component
{
public:
	testComponent2(GameObject* gameObject) : Component(gameObject) {}

	virtual void Update() override {
		float sinus = static_cast<float>(sin(glfwGetTime())) * 3;
		if (sinus < 0) {
			sinus *= -1;
		}
		gameObject->transform.SetScale(lm::vec3(1 + sinus));
	}
};
