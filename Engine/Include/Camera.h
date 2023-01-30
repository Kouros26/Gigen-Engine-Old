#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	lm::mat4 CreateViewMatrix();
	lm::mat4 GetViewMatrix() const;

	static void SetFov(float fov);
	static void SetNear(float near);
	static void SetFar(float far);
	static void SetRatio(float ratio);
	static lm::mat4 GetProjectionMatrix();

private:
	static void UpdateProjectionMatrix();

	lm::mat4 view;

	inline static lm::mat4 projectionMatrix;
	inline static float currentFov;
	inline static float currentNear;
	inline static float currentFar;
	inline static float currentRatio;
};

inline void Camera::SetFov(float fov)
{
	currentFov = fov;
	UpdateProjectionMatrix();
}

inline void Camera::SetNear(float near)
{
	currentNear = near;
	UpdateProjectionMatrix();
}

inline void Camera::SetFar(float far)
{
	currentFar = far;
	UpdateProjectionMatrix();
}

inline void Camera::SetRatio(float ratio)
{
	currentRatio = ratio;
	UpdateProjectionMatrix();
}

inline lm::mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

inline void Camera::UpdateProjectionMatrix()
{
	projectionMatrix = lm::mat4::PerspectiveProjection(currentFov, currentRatio, currentNear, currentFar);
	projectionMatrix[1][1] *= -1;
}
