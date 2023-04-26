#pragma once
#include "RigidBody.h"

class BoxRigidBody : public RigidBody
{
	lm::FVec3 halfExtents;

public:

	BoxRigidBody(const lm::FVec3& pHalfExtents, const lm::FVec3& pScale, const lm::FVec3& pPos, float pMass, GameObject* pOwner);
	~BoxRigidBody();

	const lm::FVec3& GetHalfExtents();
};