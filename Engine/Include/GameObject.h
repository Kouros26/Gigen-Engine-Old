#pragma once
#include "Transform.h"
#include <vector>

class GameObject
{
public:
	GameObject();
	GameObject(std::string name);
	~GameObject();

	virtual void Update();

	std::string GetName();

	void AddComponent(class Component* newComponent);

	//create New component of type and return the new Component
	template<class T>
	T* AddNewComponent();

	//return first component of type
	template<class T>
	T* GetComponent();

	//return vector of all components of type
	template<class T>
	std::vector<T*> GetComponents();

	//remove all components of type
	template<class T>
	void RemoveComponents();

	Transform transform;
private:
	std::string name;
	unsigned int id;

	std::vector<class Component*> components;

	void UpdateRender();
	void UpdateComponents() const;

	//use so every gameObject has a different id
	static unsigned int gameObjectCounter;
};

template<class T>
inline T* GameObject::AddNewComponent() {
	T* newComp = new T(this);
	AddComponent(newComp);
	return newComp;
}

template<class T>
inline T* GameObject::GetComponent()
{
	for (int i = 0; i < components.size(); i++)
	{
		T* comp = static_cast<T*>(components[i]);
		if (comp)
		{
			return comp;
		}
	}
	return nullptr;
}

template<class T>
inline std::vector<T*> GameObject::GetComponents()
{
	std::vector<T*> comps;
	for (int i = 0; i < components.size(); i++)
	{
		T* comp = dynamic_cast<T*>(components[i]);
		if (comp)
		{
			comps.push_back(comp);
		}
	}
	return comps;
}

template<class T>
inline void GameObject::RemoveComponents()
{
	for (int i = 0; i < components.size(); i++)
	{
		T* comp = dynamic_cast<T*>(components[i]);
		if (comp)
		{
			delete comp;
			components.erase(components.begin() + i);
		}
	}
}
