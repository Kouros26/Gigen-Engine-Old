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

	std::function<void(const Collision& collision)> triggerEnter =
		[pOwner](const Collision& collision)
	{
		pOwner->OnTriggerEnter(collision);
	};

	std::function<void(const Collision& collision)> triggerExit =
		[pOwner](const Collision& collision)
	{
		pOwner->OnTriggerExit(collision);
	};

	collisionCallBacks = new CollisionCallBacks();
	collisionCallBacks->onEnter = CollisionEnterCallBack(enter);
	collisionCallBacks->onExit = CollisionExitCallBack(exit);
	collisionCallBacks->triggerEnter = CollisionEnterCallBack(triggerEnter);
	collisionCallBacks->triggerExit = CollisionExitCallBack(triggerExit);
	body->setUserPointer(owner);

	WorldPhysics::GetInstance().AddRigidBodyInWorld(*body);
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

void CapsuleRigidBody::SetRadius(float pRadius)
{
	btCapsuleShape* shape = (btCapsuleShape*)rbShape;
	btVector3 localScale(shape->getLocalScaling());
	localScale.setX(pRadius);
	shape->setLocalScaling(localScale);
	radius = pRadius;
}

void CapsuleRigidBody::SetHeight(float pHeight)
{
	btCapsuleShape* shape = (btCapsuleShape*)rbShape;
	btVector3 localScale(shape->getLocalScaling());
	localScale.setY(pHeight);
	shape->setLocalScaling(localScale);
	height = pHeight;
}