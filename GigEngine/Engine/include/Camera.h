#pragma once
#include "GameObject.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();

	lm::FMat4 CreateViewMatrix();

	[[nodiscard]] float GetFov() const;
	[[nodiscard]] float GetNear() const;
	[[nodiscard]] float GetFar() const;
	[[nodiscard]] float GetRatio() const;

	void SetFov(float fov);
	void SetNear(float near);
	void SetFar(float far);
	void SetRatio(float ratio);
	lm::FMat4 GetProjectionMatrix();

	lm::FVec3 GetFront();
	lm::FVec3 GetUp();
	lm::FVec3 GetRight();
	virtual std::string GetType() override;

private:
	void UpdateProjectionMatrix();

	lm::FMat4 projectionMatrix;
	float currentFov = 90;
	float currentNear = 0.1f;
	float currentFar = 1000;
	float currentRatio;
};
