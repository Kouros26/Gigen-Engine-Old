#include "EditorCamera.h"
#include "Application.h"
#include "Inputs.h"
#include "Watch.h"

#include "Transform.h"
#include "Vec3/FVec3.hpp"
#include "Window.h"

#include "WorldPhysics.h"

EditorCamera::EditorCamera()
{
	GetTransform().SetWorldPosition({ 0,10,0 });
}

EditorCamera::~EditorCamera()
= default;

void EditorCamera::Update()
{
	ChangeSpeed();
	Move();
	Look();
}

void EditorCamera::ChangeSpeed()
{
	if (GigInput::Inputs::GetKey(GigInput::Keys::LEFT_SHIFT) && !pressLeftShift)
	{
		speed *= speedStep;

		if (speed > speedMax)
			speed = speedMax;

		pressLeftShift = true;
	}

	if (!GigInput::Inputs::GetKey(GigInput::Keys::LEFT_SHIFT))
		pressLeftShift = false;

	if (GigInput::Inputs::GetKey(GigInput::Keys::RIGHT_SHIFT) && !pressRightShift)
	{
		speed -= speedStep;

		if (speed < 0)
			speed = 0;

		pressRightShift = true;
	}

	if (!GigInput::Inputs::GetKey(GigInput::Keys::RIGHT_SHIFT))
		pressRightShift = false;

	HitResult result;
	std::vector<GameObject*> ignored;
	ignored.push_back(this);
	if (GigInput::Inputs::GetKey(GigInput::Keys::TAB))
	{
		if (WorldPhysics::RayCast(GetTransform().GetWorldPosition(), GetFront() * 100, result, RayCastDebug::Timer, 5, ignored))
		{
			std::cout << "Raycast hit " << result.hitObject->GetName() << std::endl;
		}
	}
}

void EditorCamera::Move()
{
	const float scaleSpeed = speed * static_cast<float>(Time::GetDeltaTime());

	if (GigInput::Inputs::GetKey(GigInput::Keys::W) || GigInput::Inputs::GetKey(GigInput::Keys::UP))
		GetTransform().AddPosition(GetFront() * scaleSpeed);

	if (GigInput::Inputs::GetKey(GigInput::Keys::S) || GigInput::Inputs::GetKey(GigInput::Keys::DOWN))
		GetTransform().AddPosition(GetFront() * -scaleSpeed);

	if (GigInput::Inputs::GetKey(GigInput::Keys::A) || GigInput::Inputs::GetKey(GigInput::Keys::LEFT))
		GetTransform().AddPosition(-GetRight() * -scaleSpeed);

	if (GigInput::Inputs::GetKey(GigInput::Keys::D) || GigInput::Inputs::GetKey(GigInput::Keys::RIGHT))
		GetTransform().AddPosition(-GetRight() * scaleSpeed);

	if (GigInput::Inputs::GetKey(GigInput::Keys::E) || GigInput::Inputs::GetKey(GigInput::Keys::SPACE))
		GetTransform().AddPosition(GetUp() * scaleSpeed);

	if (GigInput::Inputs::GetKey(GigInput::Keys::Q) || GigInput::Inputs::GetKey(GigInput::Keys::LEFT_CONTROL))
		GetTransform().AddPosition(GetUp() * -scaleSpeed);

	if (GigInput::Inputs::GetMouse().wheelClick)
	{
		GetTransform().AddPosition(GetRight() * GigInput::Inputs::GetMouse().mouseOffsetX);
		GetTransform().AddPosition(GetUp() * -GigInput::Inputs::GetMouse().mouseOffsetY);
	}

	if (GigInput::Inputs::GetMouse().wheelOffsetY != 0)
	{
		GetTransform().AddPosition(GetFront() * GigInput::Inputs::GetMouse().wheelOffsetY);
		GigInput::Inputs::UpdateMouseWheelOffset(0);
	}
}

void EditorCamera::Look()
{
	if (GigInput::Inputs::GetMouse().rightClick == 1)
	{
		Application::GetWindow().setCursorShow(false);
		const float Ry = static_cast<float>(GigInput::Inputs::GetMouse().mouseOffsetX * static_cast<double>(sensitivity));
		const float Rx = static_cast<float>(GigInput::Inputs::GetMouse().mouseOffsetY * static_cast<double>(sensitivity));

		const lm::FVec3 rot = GetTransform().GetWorldRotation();

		const lm::FVec3 vecRot = { -Rx, Ry, 0 };
		GetTransform().AddRotation(vecRot);
	}

	else if (GigInput::Inputs::GetMouse().rightClick == 0)
		Application::GetWindow().setCursorShow(true);
}