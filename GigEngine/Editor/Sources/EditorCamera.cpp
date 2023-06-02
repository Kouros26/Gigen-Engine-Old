#include "EditorCamera.h"
#include "Application.h"
#include "Inputs.h"
#include "Watch.h"
#include "GameObjectManager.h"

#include "Transform.h"
#include "Vec3/FVec3.hpp"
#include "Window.h"

#include "WorldPhysics.h"

EditorCamera::EditorCamera()
{
	GetTransform().SetWorldPosition({ 0, 10, 0 });
}

EditorCamera::~EditorCamera()
= default;

void EditorCamera::Update()
{
	ChangeSpeed();
	Move();

	if (GigInput::Inputs::GetMouse().isOnViewPort)
	{
		Translate();
		Zoom();
		Look();
	}
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
}

void EditorCamera::Translate()
{
	if (GigInput::Inputs::GetMouse().wheelClick)
	{
		Application::GetWindow().SetMouseIcon(CursorShape::GRAB);
		GetTransform().AddPosition(GetRight() * GigInput::Inputs::GetMouse().mouseOffsetX * static_cast<float>(Time::GetDeltaTime()));
		GetTransform().AddPosition(GetUp() * -GigInput::Inputs::GetMouse().mouseOffsetY * static_cast<float>(Time::GetDeltaTime()));
	}
}

void EditorCamera::Zoom()
{
	if (GigInput::Inputs::GetMouse().wheelOffsetY != 0)
	{
		GetTransform().AddPosition(GetFront() * GigInput::Inputs::GetMouse().wheelOffsetY);
		GigInput::Inputs::UpdateMouseWheelOffset(0);
	}
}

void EditorCamera::Look()
{
	if (GigInput::Inputs::GetMouse().rightClick)
	{
		Application::GetWindow().SetMouseIcon(CursorShape::EYE);
		const float Ry = static_cast<float>(GigInput::Inputs::GetMouse().mouseOffsetX * static_cast<double>(sensitivity));
		const float Rx = static_cast<float>(GigInput::Inputs::GetMouse().mouseOffsetY * static_cast<double>(sensitivity));

		const lm::FVec3 rot = GetTransform().GetWorldRotation();

		const lm::FVec3 vecRot = { -Rx, Ry, 0 };
		GetTransform().AddRotation(vecRot);
	}

	if (GigInput::Inputs::GetMouse().OnLeftClick())
	{
		HitResult result;

		//if (WorldPhysics::GetInstance().SimpleRayCast(GetTransform().GetWorldPosition(), GetFront() * 1000, result, RayCastDebug::None, 5, lm::FVec3(1)))
		//{
		//	GameObjectManager::SetFocusedGameObject(result.hitObject);
		//}
	}
}