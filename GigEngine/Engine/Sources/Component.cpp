#include "Component.h"

Component::Component(GameObject* gameObject)
    :gameObject(gameObject)
{}

GameObject* Component::GetGameObject() const
{
    return gameObject;
}

std::string Component::GetType()
{
    const std::string type(typeid(this).name());
    return type.substr(6, type.size() - 16);
}

void Component::Update(float pDeltaTime)
{
}

void Component::LateUpdate(float pDeltaTime)
{
}

Component::~Component()
{
}

void Component::Start()
{
}

void Component::Awake()
{
}