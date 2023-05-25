#pragma once
#include "RigidBody.h"

class CapsuleRigidBody : public RigidBody
{
	float radius;
	float height;

public:

	CapsuleRigidBody(float pRadius, float pHeight, const lm::FVec3& pScale, const lm::FVec3& pPos, float pMass,
	                 GameObject* pOwner);

	~CapsuleRigidBody();

	[[nodiscard]] float GetRadius() const;
	[[nodiscard]] float GetHeight() const;

	void SetRadius(float pRadius);
	void SetHeight(float pHeight);
};
