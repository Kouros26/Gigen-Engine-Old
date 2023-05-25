#include "Object.h"
#include <typeinfo>

Object::Object()
{
	objectIndex++;
	id = objectIndex;

	name = "Object " + std::to_string(id);
}

Object::Object(const std::string& name)
	: Object()
{
	if (!name.empty())
		this->name = name;
}

Object::~Object()
{
}

std::string Object::GetName() const
{
	return name;
}

void Object::SetName(const std::string& pName)
{
	if (pName.length() == 0)
	{
		name = "Object " + std::to_string(id);
		return;
	}

	name = pName;
}

unsigned int Object::GetId() const
{
	return id;
}

std::string Object::GetType()
{
	const std::string type(typeid(this).name());
	return type.substr(6, type.size() - 16);
}

bool Object::IsActive() const
{
	return isActive;
}

void Object::SetActive(bool b)
{
	isActive = b;
}