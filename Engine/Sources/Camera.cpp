#include "Camera.h"

Camera::Camera()
	:GameObject("Camera")
{
	CreateViewMatrix();
}

Camera::~Camera()
{
}

lm::mat4 Camera::CreateViewMatrix()
{
	view = lm::mat4::LookAt(transform.GetPosition(), transform.GetPosition() + transform.GetFront(), transform.GetUp());
	return view;
}

lm::mat4 Camera::GetViewMatrix() const
{
	return view;
}
