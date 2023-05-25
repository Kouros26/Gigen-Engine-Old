#pragma once
#include "Watch.h"
#include "GameObject.h"

class Component
{
public:
    Component(GameObject* gameObject);
    virtual ~Component();

    virtual void Awake();
    virtual void Start();
    virtual void Update(float pDeltaTime);
    virtual void LateUpdate(float pDeltaTime);
    virtual Component* Clone(GameObject* newGameObject) = 0;

    Component(const Component& other) = default;
    Component(Component&& other) noexcept = default;
    Component& operator=(const Component& other) = default;
    Component& operator=(Component&& other) noexcept = default;

    [[nodiscard]] GameObject* GetGameObject() const;

    virtual std::string GetType();

protected:
    GameObject* gameObject;
};

class TestComponent : public Component
{
public:
    TestComponent(GameObject* obj) : Component(obj) {}

    virtual void Update(float pDeltaTime) override {
        gameObject->GetTransform().AddPosition(lm::FVec3(0, 0.5f, 0.f) * Time::GetDeltaTime());
    };

    virtual Component* Clone(GameObject* newGameObject) override {
        return new TestComponent(newGameObject);
    }
};

class testComponent2 : public Component
{
public:
    testComponent2(GameObject* obj) : Component(obj) {};

    virtual void Update(float pDeltaTime) override {
        gameObject->GetTransform().AddRotation(lm::FVec3(0, 0, 20.f) * Time::GetDeltaTime());
    };

    virtual Component* Clone(GameObject* newGameObject) override {
        return new testComponent2(newGameObject);
    }
};