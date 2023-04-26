#include "CapsuleRigidBody.h"
#include <WorldPhysics.h>

CapsuleRigidBody::CapsuleRigidBody(float pRadius, float pHeight, const lm::FVec3& pScale, const lm::FVec3& pPos, float pMass,
	GameObject* pOwner)
		: RigidBody(pOwner), radius(pRadius), height(pHeight)
{
	scale = pScale;
	mass = pMass;

	rbShape = new btCapsuleShape(radius, height);
	rbShape->setLocalScaling({ pScale.x, pScale.y, pScale.z });

	btVector3 inertia(0, 0, 0);

	if (mass > 0)
		rbShape->calculateLocalInertia(mass, inertia);

	transform.setIdentity();
	transform.setOrigin({ pPos.x, pPos.y, pPos.z });
	motionState = new CustomMotionState(transform, pOwner);

	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, rbShape, inertia);
	body = new btRigidBody(info);

	std::function<void(Collision collision)> enter =
		[pOwner](const Collision& collision)
	{

		pOwner->OnCollisionEnter(collision);
	};

	std::function<void(Collision collision)> exit =
		[pOwner](const Collision& collision)
	{
		pOwner->OnCollisionExit(collision);
	};

	collisionCallBacks = new CollisionCallBacks();
	collisionCallBacks->onEnter = CollisionEnterCallBack(enter);
	collisionCallBacks->onExit = CollisionExitCallBack(exit);
	body->setUserPointer(owner);

	WorldPhysics::AddRigidBodyInWorld(body);
}

CapsuleRigidBody::~CapsuleRigidBody()
{
	delete rbShape;
	delete motionState;
	delete collisionCallBacks;
}

float CapsuleRigidBody::GetRadius() const
{
	return radius;
}

float CapsuleRigidBody::GetHeight() const
{
	return height;
}