#include "SphereRigidBody.h"

#include "WorldPhysics.h"

SphereRigidBody::SphereRigidBody(float pRadius, const lm::FVec3& pScale, const lm::FVec3& pPos, float pMass,
	GameObject* pOwner)
	: RigidBody(pOwner), radius(pRadius)
{
	scale = pScale;
	mass = pMass;

	rbShape = new btSphereShape(radius);
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

float SphereRigidBody::GetRadius() const
{
	return radius;
}

void SphereRigidBody::SetRadius(float pRadius)
{
	btSphereShape* shape = (btSphereShape*)rbShape;
	radius = pRadius;
	shape->setUnscaledRadius(radius);
}