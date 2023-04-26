#include "CustomMotionState.h"

#include "Watch.h"
#include "Vec4/Vec4.h"

CustomMotionState::CustomMotionState(const btTransform& transform, GameObject* owner)
	: btDefaultMotionState(transform), owner(owner)
{
}

void CustomMotionState::GetWorldTransform(btScalar* pTransform) const
{
	btTransform transform;
	getWorldTransform(transform);
	transform.getOpenGLMatrix(pTransform);
}

void CustomMotionState::setWorldTransform(const btTransform& pCenterOfMassWorldTrans)
{
	btDefaultMotionState::setWorldTransform(pCenterOfMassWorldTrans);

	btScalar worldMatrix[16];
	btTransform worldTransform;
	getWorldTransform(worldTransform);
	worldTransform.getOpenGLMatrix(worldMatrix);

	physicsMatrix = ScalarToMat4(worldMatrix);
	lm::FMat4::Decompose(physicsMatrix, physicsPosition, physicsRotation, physicsScale);
	owner->GetTransform().AddPosition(physicsPosition - owner->GetTransform().GetWorldPosition());
}

lm::FMat4 CustomMotionState::ScalarToMat4(const btScalar * pScalar)
{
	lm::FVec4 r1(pScalar[0], pScalar[1], pScalar[2], pScalar[3]);
	lm::FVec4 r2(pScalar[4], pScalar[5], pScalar[6], pScalar[7]);
	lm::FVec4 r3(pScalar[8], pScalar[9], pScalar[10], pScalar[11]);
	lm::FVec4 r4(pScalar[12], pScalar[13], pScalar[14], pScalar[15]);

	return { r1, r2, r3, r4 };
}
