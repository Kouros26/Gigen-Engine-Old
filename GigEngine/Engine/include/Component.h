#pragma once
#include "Watch.h"
#include "GameObject.h"

class Component
{
public:
    Component(GameObject* gameObject);
    virtual ~Component();

    virtual void Start();
    virtual void Update();

    virtual Component* Clone(GameObject* newGameObject) = 0;

    Component(const Component& other) = default;
    Component(Component&& other) noexcept = default;
    Component& operator=(const Component& other) = default;
    Component& operator=(Component&& other) noexcept = default;

protected:
    GameObject* gameObject;
};

class Script : public Component
{
public:
	Script(GameObject* obj) : Component(obj) {}

	virtual void Awake();
	virtual void LateUpdate();
};

class TestScript : public Script
{
public:
	TestScript(GameObject* obj) : Script(obj) {}

	void Awake() override;
	void Start() override;
	void Update() override;
	void LateUpdate() override;

    virtual Component* Clone(GameObject* newGameObject) override {
        return new TestScript(newGameObject);
    }
};

class TestComponent : public Component
{
public:
    TestComponent(GameObject* obj) : Component(obj) {}

    virtual void Update() override {
        gameObject->GetTransform().AddPosition(lm::FVec3(0, 50.f, 0.f) * Time::GetDeltaTime());
    }

    virtual Component* Clone(GameObject* newGameObject) override {
        return new TestComponent(newGameObject);
    }
};

class testComponent2 : public Component
{
public:
	testComponent2(GameObject* obj) : Component(obj) {}

    virtual void Update() override {
        gameObject->GetTransform().AddRotation(lm::FVec3(0, 0, 200.f) * Time::GetDeltaTime());
    }

    virtual Component* Clone(GameObject* newGameObject) override {
        return new testComponent2(newGameObject);
    }
};