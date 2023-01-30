#include "GameObject.h"
#include "Component.h"

unsigned int GameObject::gameObjectCounter = 0;

GameObject::GameObject()
{
	gameObjectCounter++;
	id = gameObjectCounter;

	name = "GameObject " + id;
}

GameObject::GameObject(std::string name)
	:GameObject()
{
	if (!name.empty()) {
		name = name;
	}
}

GameObject::~GameObject()
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i])
			delete components[i];
	}
}

void GameObject::Update()
{
	UpdateComponents();
	UpdateRender();
}

std::string GameObject::GetName()
{
	return name;
}

void GameObject::UpdateRender()
{
}

void GameObject::UpdateComponents() const
{
	for (const auto& component : components)
	{
		component->Update();
	}
}

void GameObject::AddComponent(Component* newComponent)
{
	components.push_back(newComponent);
}