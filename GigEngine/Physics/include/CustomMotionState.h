#pragma once
#include <btBulletCollisionCommon.h>
#include "Mat4/FMat4.hpp"
#include "Vec3/FVec3.hpp"
#include "GameObject.h"

class CustomMotionState : public btDefaultMotionState
{
	GameObject* owner;
	lm::FMat4 physicsMatrix;

	lm::FVec3 physicsPosition;
	lm::FVec3 physicsRotation;
	lm::FVec3 physicsScale;

public:
	CustomMotionState(const btTransform& transform, GameObject* owner);

	void GetWorldTransform(btScalar* pTransform) const;
	void setWorldTransform(const btTransform& pCenterOfMassWorldTrans) override;

	static lm::FMat4 ScalarToMat4(const btScalar* pScalar);
};
