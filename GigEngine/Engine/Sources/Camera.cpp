#include "Camera.h"
#include "Application.h"

Camera::Camera()
	:GameObject("Camera")
{
	CreateViewMatrix();

	currentRatio = Application::GetWindow().GetViewPortRatio();
	UpdateProjectionMatrix();
}

Camera::~Camera()
{
}

lm::FMat4 Camera::CreateViewMatrix()
{
	return lm::FMat4::LookAt(GetTransform().GetWorldPosition(), GetTransform().GetWorldPosition() + GetFront(), GetUp());
}

float Camera::GetFov()
{
	return currentFov;
}

float Camera::GetNear()
{
	return currentNear;
}

float Camera::GetFar()
{
	return currentFar;
}

void Camera::SetFov(float fov)
{
	if (fov != currentFov)
	{
		currentFov = fov;
		UpdateProjectionMatrix();
	}
}

void Camera::SetNear(float near)
{
	if (near != currentNear)
	{
		currentNear = near;
		UpdateProjectionMatrix();
	}
}

void Camera::SetFar(float far)
{
	if (far != currentFar)
	{
		currentFar = far;
		UpdateProjectionMatrix();
	}
}

void Camera::SetRatio(float ratio)
{
	if (ratio != currentRatio)
	{
		currentRatio = ratio;
		UpdateProjectionMatrix();
	}
}

lm::FMat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::UpdateProjectionMatrix()
{
	projectionMatrix = lm::FMat4::Perspective(currentFov, currentRatio, currentNear, currentFar);
}

lm::FVec3 Camera::GetFront()
{
	lm::FMat4 inverse = lm::FMat4::Inverse(GetTransform().GetMatrix());
	const lm::FVec3 front = inverse[2];
	return lm::FVec3::Normalize(front);
}

lm::FVec3 Camera::GetUp()
{
	lm::FMat4 inverse = lm::FMat4::Inverse(GetTransform().GetMatrix());
	const lm::FVec3 up = inverse[1];
	return lm::FVec3::Normalize(up);
}

lm::FVec3 Camera::GetRight()
{
	lm::FMat4 inverse = lm::FMat4::Inverse(GetTransform().GetMatrix());
	const lm::FVec3 right = inverse[0];
	return lm::FVec3::Normalize(right);
}