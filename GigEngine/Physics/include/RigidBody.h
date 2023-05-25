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
	RBState state = RBState::DYNAMIC;
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
	void RemoveRBState(const RBState& pState) const;
	void SetMotionState(CustomMotionState* pMotionState);

    void SetRigidBodyPosition(const lm::FVec3& pNewPosition);
    void SetRigidBodyRotation(const lm::FVec3& pNewRotation);
    void SetRigidBodyRotation(const lm::FQuat& pNewRotation);
    void SetRigidBodyScale(const lm::FVec3& pNewScale) const;

    void AddRigidBodyPosition(const lm::FVec3& pAddedPosition);
    void AddRigidBodyRotation(const lm::FVec3& pAddedRotation);
    void AddRigidBodyRotation(const lm::FQuat& pAddedRotation);
    void AddRigidBodyScale(const lm::FVec3& pAddedScale) const;

    void AddForce(const float pValue) const;
    void AddForce(const lm::FVec3& pValue) const;
    void AddTorque(const float pValue) const;
    void AddTorque(const lm::FVec3& pValue) const;
    void SetVelocity(const lm::FVec3& pValue) const;
    void SetAngularVelocity(const lm::FVec3& pValue) const;
    [[nodiscard]] float GetFriction() const;
    void SetFriction(const float pValue) const;
    void SetBounciness(const float pValue) const;
    [[nodiscard]] lm::FVec3 GetLinearVelocity() const;
    [[nodiscard]] float GetBounciness() const;
    [[nodiscard]] lm::FVec3 GetAngularVelocity() const;
    void SetLinearFactor(const float pValue) const;
    void SetLinearFactor(const lm::FVec3& pValue) const;
    void SetAngularFactor(const float pValue) const;
    [[nodiscard]] lm::FVec3 GetLinearFactor() const;
    [[nodiscard]] lm::FVec3 GetAngularFactor() const;
    static bool IsTrigger();
    void SetTrigger(const bool pIsTrigger);
    void AddImpulse(const float pValue) const;
    void AddImpulse(const lm::FVec3& pValue) const;

    [[nodiscard]] bool IsGravityEnabled() const;
    [[nodiscard]] btRigidBody* GetRigidBody() const;
    [[nodiscard]] CustomMotionState* GetMotionState() const;
    [[nodiscard]] btCollisionShape* GetRBShape() const;
    [[nodiscard]] CollisionCallBacks* GetCallBacks() const;
    RigidBodyType& GetShapeType();
    btScalar& GetMass();
    int GetCollisionFlag() const;
    const lm::FVec3& GetScale();
    btTransform GetTransfrom() const;
    void SetMass(const float pValue);
	void SetScale(const lm::FVec3& pNewScale);
    void SetGravityEnabled(const bool pState) const;
    void ClearForces() const;
    void SetGravity(const lm::FVec3& pValue) const;
    [[nodiscard]] lm::FVec3 GetGravity() const;
};