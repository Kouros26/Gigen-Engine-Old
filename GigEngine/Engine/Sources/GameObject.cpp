#include "GameObject.h"
#include "WorldPhysics.h"
#include "BoxRigidBody.h"
#include "CapsuleRigidBody.h"
#include "Model.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "GameObjectManager.h"
#include "Component.h"
#include "ScriptInterpreter.h"
#include "Behaviour.h"
#include "SphereRigidBody.h"
#include "LuaBindComponent.h"
#include <filesystem>
#include <iostream>
#include <fstream>

#include "Animator.h"

GameObject::GameObject() : Object()
{
}

GameObject::GameObject(const std::string& name)
	: Object(name)
{
}

GameObject::GameObject(const std::string& name, const lm::FVec3& position, const lm::FVec3& rotation,
	const lm::FVec3& scale)
	: Object(name), transform(position, rotation, scale)
{
}

GameObject::GameObject(const lm::FVec3& position, const lm::FVec3& rotation, const lm::FVec3& scale)
	: Object(), transform(position, rotation, scale)
{
}

GameObject::GameObject(const GameObject& other)
	: Object(other.GetName())
{
	transform = other.transform;

	for (const auto& component : other.components)
		components.push_back(component->Clone(this));

    for (const auto& child : other.children)
        AddChild(*GameObjectManager::CreateGameObject(*child));

    if (other.model != nullptr)
        model = ResourceManager::Get<Model>(other.model->GetFilePath());
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this == &other)
		return *this;

	SetName(other.GetName() + " " + std::to_string(GetId()));

	transform = other.transform;

	for (const auto& component : other.components)
		components.push_back(component->Clone(this));

    for (const auto& child : other.children)
        AddChild(*GameObjectManager::CreateGameObject(*child));

	if (other.model != nullptr)
		model = ResourceManager::Get<Model>(other.model->GetFilePath());

	return *this;
}

GameObject::~GameObject()
{
	for (const auto& component : components)
		delete component;

	delete rigidBody;

    if (parent)
        parent->RemoveChild(*this);
}

std::string GameObject::GetType()
{
	const std::string type(typeid(this).name());
	return type.substr(6, type.size() - 16);
}

void GameObject::CreateBoxRigidBody(const lm::FVec3& halfExtents = { 1.0f }, const lm::FVec3& scale = { 1.0f }, float mass = 1.0f)
{
	delete rigidBody;

    rigidBody = new BoxRigidBody(halfExtents, scale, transform.GetWorldPosition(), mass, this);
    rigidBody->GetShapeType() = RigidBodyType::BOX;
    transform.SetOwnerRigidBody(rigidBody);
}

void GameObject::CreateCapsuleRigidBody(float radius, float height, const lm::FVec3& scale, float mass)
{
	delete rigidBody;

    rigidBody = new CapsuleRigidBody(radius, height, scale, transform.GetWorldPosition(), mass, this);
    rigidBody->GetShapeType() = RigidBodyType::CAPSULE;
    transform.SetOwnerRigidBody(rigidBody);
}

void GameObject::CreateSphereRigidBody(float radius, const lm::FVec3& scale, float mass)
{
	delete rigidBody;

    rigidBody = new SphereRigidBody(radius, scale, transform.GetWorldPosition(), mass, this);
    rigidBody->GetShapeType() = RigidBodyType::SPHERE;
    transform.SetOwnerRigidBody(rigidBody);
}

Animator* GameObject::GetAnimator()
{
	return GetComponent<Animator>();
}

void GameObject::SetModel(std::string const& filePath)
{
	model = ResourceManager::Get<Model>(filePath);
	if (!texture)
	{
		if (filePath.find(".fbx") != std::string::npos || filePath.find(".FBX") != std::string::npos)
		{
			texture = ResourceManager::Get<Texture>(g_defaultTexturePath2);
		}
		else
		{
			texture = ResourceManager::Get<Texture>(g_defaultTexturePath);
		}
	}
}

void GameObject::SetModelWithPathLua(const std::string& filePath)
{
	const std::string& path = "../../../Resources/";
	SetModel(path + filePath);
}

void GameObject::SetModel(Model* pModel)
{
	model = pModel;
}

Model* GameObject::GetModel() const
{
	return model;
}

void GameObject::SetTexture(const std::string& filePath)
{
	texture = ResourceManager::Get<Texture>(filePath);
	if (!texture->isValid())
	{
		std::cout << "texture invalid" << std::endl;
		texture = ResourceManager::Get<Texture>(g_defaultTexturePath);
	}
}

void GameObject::SetTextureWithPathLua(const std::string& filePath)
{
	const std::string& path = "../../../Resources/";
	SetTexture(path + filePath);
}

Texture* GameObject::GetTexture() const
{
	return texture;
}

void GameObject::AddChild(GameObject& child)
{
    if (child.parent == this)
        return;

    if (child.parent != nullptr)
        child.parent->RemoveChild(child);

    child.parent = this;

    child.GetTransform().AssignLocalPosition(child.GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition());
    child.GetTransform().AssignLocalScale(child.GetTransform().GetWorldScale() / GetTransform().GetWorldScale());

    children.push_back(&child);
}

void GameObject::RemoveChild(GameObject& child)
{
    if (child.parent != this)
        return;

    child.GetTransform().AssignLocalPosition(child.GetTransform().GetWorldPosition());
    child.GetTransform().AssignLocalRotation(child.GetTransform().GetWorldRotation());

    child.parent = nullptr;
    children.remove(&child);
}

void GameObject::OnCollisionEnter(const Collision& collision)
{
    if (GigScripting::LuaBindComponent::delegateFunctions.OnCollisionEnter)
    {
        GigScripting::LuaBindComponent::delegateFunctions.OnCollisionEnter(const_cast<Collision*>(&collision)->other);
    }
}

void GameObject::OnCollisionExit(const Collision& collision)
{
    if (GigScripting::LuaBindComponent::delegateFunctions.OnCollisionExit)
    {
        GigScripting::LuaBindComponent::delegateFunctions.OnCollisionExit(const_cast<Collision*>(&collision)->other);
    }
}

void GameObject::UpdateRender() const
{
	if (model && IsActive())
		model->Draw(texture);
}

void GameObject::UpdateComponents() const
{
	if (IsActive())
	{
		for (const auto& component : components)
			component->Update(Time::GetDeltaTime());
	}
}

void GameObject::LateUpdate() const
{
	if (IsActive())
	{
		for (const auto script : components)
			script->LateUpdate(Time::GetDeltaTime());
	}
}

void GameObject::CheckForScript(Component* pComponent)
{
	if (const auto script = dynamic_cast<GigScripting::Behaviour*>(pComponent))
	{
		SCRIPT_INTERPRETER.RegisterBehaviour(script);
		script->Awake();
	}
}

GigScripting::Behaviour* GameObject::GetBehaviour(const std::string& pName) const
{
    for (const auto& component : components)
    {
        if (const auto script = dynamic_cast<GigScripting::Behaviour*>(component))
        {
            if (script->GetScriptName() == pName)
                return script;
        }
    }

	return nullptr;
}

void GameObject::RemoveScript(GigScripting::Behaviour* pScript)
{
	for (int i = 0; i < components.size(); ++i)
	{
		if (components[i] == pScript)
		{
			delete components[i];
			components.erase(components.begin() + i);
			break;
		}
	}
}

void GameObject::AddScript(const std::string& path)
{
	std::string name = path.substr(path.find_last_of("\\") + 1, path.find_last_of(".") - path.find_last_of("\\") - 1);
	if (GetBehaviour(name))
		return;
	AddComponent<GigScripting::Behaviour>(name);
}

void GameObject::AddScript()
{
	std::string path = "../../../Resources/Editor/Scripts/";
	std::string name = "NewScript";
	std::string extension = ".lua";
	int i = 0;
	std::string fullName = path + name + std::to_string(i) + extension;
	std::string fileName = name + std::to_string(i);
	while (std::filesystem::exists(fullName))
	{
		fileName = name + std::to_string(i);
		fullName = path + name + std::to_string(i) + extension;
		i++;
	}

	std::ofstream script(fullName);

	script << "local " << fileName << " = \n { \n } \n \n function " << fileName << ":Start() \n \n end \n \n function " << fileName << ":Update(deltaTime) \n \n end \n \n return " << fileName;

	script.close();

	AddComponent<GigScripting::Behaviour>(fileName);
}

void GameObject::UpdateHierarchy()
{
	if (this->parent != nullptr)
	{
		GetTransform().AssignWorldRotation(parent->GetTransform().GetWorldRotation() + GetTransform().GetLocalRotation());
		GetTransform().AssignWorldPosition(parent->GetTransform().GetWorldPosition() + (parent->GetTransform().GetOrientation() * GetTransform().GetLocalPosition()));
		GetTransform().AssignWorldScale(parent->GetTransform().GetWorldScale() * GetTransform().GetLocalScale());
	}

	else
	{
		GetTransform().AssignWorldRotation(GetTransform().GetLocalRotation());
		GetTransform().AssignWorldPosition(GetTransform().GetLocalPosition());
		GetTransform().AssignWorldScale(GetTransform().GetLocalScale());
	}

	for (const auto& child : this->children)
		child->UpdateHierarchy();
}

void GameObject::AddComponent(Component* newComponent)
{
	components.push_back(newComponent);

	if (const auto script = dynamic_cast<GigScripting::Behaviour*>(newComponent))
	{
		SCRIPT_INTERPRETER.RegisterBehaviour(script);
		script->Awake();
	}
}

unsigned GameObject::GetComponentCount() const
{
	return static_cast<unsigned>(components.size());
}

Transform& GameObject::GetTransform()
{
	return transform;
}

bool GameObject::IsAParent(GameObject* obj) const
{
	GameObject* p = parent;
	while (p != nullptr)
	{
		if (p == obj)
		{
			return true;
		}
		p = p->GetParent();
	}
	return false;
}

GameObject*& GameObject::GetParent()
{
	return parent;
}

void GameObject::SetParent(GameObject& newParent)
{
	if (parent)
		parent->RemoveChild(*this);

	parent = &newParent;
	newParent.AddChild(*this);
}

std::list<GameObject*>& GameObject::GetChildren()
{
	return children;
}

GameObject* GameObject::GetChild(unsigned int index)
{
	if (index > children.size())
	{
		return nullptr;
	}
	auto c = children.begin();
	std::advance(c, index);
	return *c;
}

unsigned int GameObject::GetChildrenCount() const
{
	return children.size();
}

RigidBody* GameObject::GetRigidBody() const
{
	return rigidBody;
}

void GameObject::RemoveRigidBody()
{
    delete rigidBody;
    rigidBody = nullptr;
}

void GameObject::SetActive(bool b)
{
	Object::SetActive(b);
	for (GameObject* child : children)
	{
		child->SetActive(b);
	}
}

bool GameObject::IsActive() const
{
	return isActive;
}
