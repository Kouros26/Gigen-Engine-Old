#pragma once
#include <functional>
#include "CustomMotionState.h"
#include "GameObjectManager.h"

struct Collision;
enum class RBState
{
	DYNAMIC,
	KINETIC,
	STATIC
};

enum class RigidBodyType
{
	BOX,
	CAPSULE,
	SPHERE
};

using CollisionEnterCallBack = std::function<void(Collision)>;
using CollisionExitCallBack = std::function<void(Collision)>;

struct CollisionCallBacks
{
	CollisionEnterCallBack onEnter;
	CollisionExitCallBack onExit;
};

class RigidBody
{
protected:
	btTransform transform;
	GameObject* owner;
	btRigidBody* body = nullptr;
	CustomMotionState* motionState = nullptr;
	btCollisionShape* rbShape = nullptr;
	CollisionCallBacks* collisionCallBacks = nullptr;
	RigidBodyType rbType{};
	btScalar mass{};
	lm::FVec3 scale;

public:

	RigidBody(GameObject* pOwner);
	~RigidBody();

	void SetRBState(const RBState& pState) const;
	void SetMotionState(CustomMotionState* pMotionState);

	void SetRigidBodyPosition(const lm::FVec3& pNewPosition);
	void SetRigidBodyRotation(const lm::FVec3& pNewRotation);
	void SetRigidBodyRotation(const lm::FQuat& pNewRotation);
	void SetRigidBodyScale(const lm::FVec3& pNewScale) const;

	void AddRigidBodyPosition(const lm::FVec3& pAddedPosition);
	void AddRigidBodyRotation(const lm::FVec3& pAddedRotation);
	void AddRigidBodyRotation(const lm::FQuat& pAddedRotation);
	void AddRigidBodyScale(const lm::FVec3& pAddedScale) const;

	[[nodiscard]] btRigidBody* GetRigidBody() const;
	[[nodiscard]] CustomMotionState* GetMotionState() const;
	[[nodiscard]] btCollisionShape* GetRBShape() const;
	[[nodiscard]] CollisionCallBacks* GetCallBacks() const;
	RigidBodyType& GetShapeType();
	btScalar& GetMass();
	const lm::FVec3& GetScale();

	void SetScale(const lm::FVec3& pNewScale);
	void SetGravityEnabled(const bool pState) const;
};