#pragma once
#include "RigidBody.h"

class SphereRigidBody : public RigidBody
{
	float radius;

public:

	SphereRigidBody(float pRadius, const lm::FVec3& pScale, const lm::FVec3& pPos, float pMass, GameObject* pOwner);

	[[nodiscard]] float GetRadius() const;

	void SetRadius(float pRadius);
};