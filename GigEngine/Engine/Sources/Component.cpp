#include "Component.h"

Component::Component(GameObject* gameObject)
	:gameObject(gameObject)
{}

Component::~Component()
{
}

void Component::Start()
{
}

void Component::Update()
{
}

void Script::Awake()
{
}

void Script::LateUpdate()
{
}

void TestScript::Awake()
{
	std::cout << "This is "<< gameObject->GetName() << "'s awake function" << std::endl;
}

void TestScript::Start()
{
	std::cout << "This is "<< gameObject->GetName() << "'s start function" << std::endl;
}

void TestScript::Update()
{
	std::cout << "This is "<< gameObject->GetName() << "'s update" << std::endl;
}

void TestScript::LateUpdate()
{
	std::cout << "This is " << gameObject->GetName() << "'s late update" << std::endl;
}
