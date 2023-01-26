#include "FreeCam.h"

#include "Application.h"

class Application;

FreeCam::FreeCam(GameObject* gameObject)
	:Component(gameObject)
{
}

FreeCam::~FreeCam()
= default;

void FreeCam::Update()
{
	if (Inputs::GetKey(LEFT_SHIFT) && !pressLeftShift)
	{
		speed += speedStep;
		if (speed > speedMax)
		{
			speed = speedMax;
		}
		pressLeftShift = true;
	}
	if (!Inputs::GetKey(LEFT_SHIFT))
	{
		pressLeftShift = false;
	}

	if (Inputs::GetKey(RIGHT_SHIFT) && !pressRightShift)
	{
		speed -= speedStep;
		if (speed < 0)
		{
			speed = 0;
		}
		pressRightShift = true;
	}
	if (!Inputs::GetKey(RIGHT_SHIFT))
	{
		pressRightShift = false;
	}

	const float scaleSpeed = speed * static_cast<float>(Time::GetDeltaTime());

	if (Inputs::GetKey(UP) || Inputs::GetKey('W'))
	{
		gameObject->transform.AddPosition(gameObject->transform.GetFront() * scaleSpeed);
	}
	if (Inputs::GetKey(DOWN) || Inputs::GetKey('S'))
	{
		gameObject->transform.AddPosition(gameObject->transform.GetFront() * -scaleSpeed);
	}
	if (Inputs::GetKey(LEFT) || Inputs::GetKey('A'))
	{
		gameObject->transform.AddPosition(gameObject->transform.GetRight() * -scaleSpeed);
	}
	if (Inputs::GetKey(RIGHT) || Inputs::GetKey('D'))
	{
		gameObject->transform.AddPosition(gameObject->transform.GetRight() * scaleSpeed);
	}

	if (Inputs::GetMouse().rightClick == 1)
	{
		glfwSetInputMode(Application::GetWindow().GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		const float Ry = static_cast<float>(Inputs::GetMouse().mouseOffsetX * static_cast<double>(sensitivity) * Time::GetTimeScale());
		const float Rx = static_cast<float>(Inputs::GetMouse().mouseOffsetY * static_cast<double>(sensitivity) * Time::GetTimeScale());

		gameObject->transform.AddRotation(lm::vec3(Rx, Ry, 0));
	}

	else if (Inputs::GetMouse().rightClick == 0)
		glfwSetInputMode(Application::GetWindow().GetGLFWWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}