#include "BoxRigidBody.h"
#include "GameObject.h"
#include "WorldPhysics.h"

BoxRigidBody::BoxRigidBody(const lm::FVec3& pHalfExtents, const lm::FVec3& pScale, const lm::FVec3& pPos, float pMass,
                           GameObject* pOwner)
		: RigidBody(pOwner), halfExtents(pHalfExtents)
{
	scale = pScale;
	mass = pMass;

	rbShape = new btBoxShape({ pHalfExtents.x, pHalfExtents.y, pHalfExtents.z });
	rbShape->setLocalScaling({ pScale.x, pScale.y, pScale.z });

	btVector3 inertia(0, 0, 0);

	if (mass > 0)
		rbShape->calculateLocalInertia(mass, inertia);

	transform.setIdentity();
	transform.setOrigin({ pPos.x, pPos.y, pPos.z });
	motionState = new CustomMotionState(transform, pOwner);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, rbShape, inertia);
	body = new btRigidBody(info);

	std::function<void(const Collision& collision)> enter =
		[pOwner](const Collision& collision)
	{

		pOwner->OnCollisionEnter(collision);
	};

	std::function<void(const Collision& collision)> exit =
		[pOwner](const Collision& collision)
	{
		pOwner->OnCollisionExit(collision);
	};

	collisionCallBacks = new CollisionCallBacks();
	collisionCallBacks->onEnter = CollisionEnterCallBack(enter);
	collisionCallBacks->onExit = CollisionExitCallBack(exit);
	body->setUserPointer(owner);

	WorldPhysics::GetInstance().AddRigidBodyInWorld(*body);
}

BoxRigidBody::~BoxRigidBody()
{
	delete rbShape;
	delete motionState;
	delete collisionCallBacks;
}

const lm::FVec3& BoxRigidBody::GetHalfExtents()
{
	return halfExtents;
}