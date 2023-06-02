#pragma once
#include "Vec3/FVec3.hpp"
#include <set>
#include <vector>
#include "btBulletDynamicsCommon.h"
#include "DebugDrawer.h"

class GameObject;
enum class RayCastDebug
{
    None,
    OneFrame,
    Timer,
    Forever
};

struct HitResult
{
    GameObject* hitObject;
    lm::FVec3 hitPoint;
};

struct Collision
{
    GameObject* other{};
    lm::FVec3 contactPoint{};
    float collisionStrength{};

    Collision(GameObject* pOther, const btManifoldPoint pManifold);
};

class WorldPhysics
{
public:

    void InitPhysicWorld();
    void DestroyPhysicWorld() const;

    void ClearCollisionCache();

    static bool RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd,
        HitResult& pOutHit, const RayCastDebug pDrawProperties = RayCastDebug::None,
        float pTimer = -1, const std::vector<GameObject*>& pIgnoredObjects = {},
        const lm::FVec3& pRayColor = { 0,1,0 }, const lm::FVec3& pHitColor = { 1, 0, 0 });

    static bool RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit, const RayCastDebug pDrawProperties, float pTimer);

    static bool RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit);

    static bool RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit, const RayCastDebug pDrawProperties, float pTimer, const lm::FVec3& pRayColor);

    static bool RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit,
        const RayCastDebug pDrawProperties, float pTimer, const lm::FVec3& pRayColor, const lm::FVec3& pHitColor);

    static bool SimpleRayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit, const RayCastDebug pDrawProperties, float pTimer, const lm::FVec3& pRayColor);

    void AddRigidBodyInWorld(btRigidBody& pRigidBody) const;
    void RemoveRigidBodyFromWorld(btRigidBody& pRigidBody) const;
    void UpdatePhysics(double pDeltaTime) const;
    void DrawDebug() const;

    void SetGravity(const lm::FVec3& pGravity) const;

    btDiscreteDynamicsWorld* GetWorld();

    static WorldPhysics& GetInstance();

private:

    static void TickCallBack(btDynamicsWorld* pWorld, btScalar pTimeStep);
    void CheckCollision();
    static void RayCastDebugDraw(const lm::FVec3& pStart, const lm::FVec3& pEnd, const lm::FVec3& pColor, const RayCastDebug& pDrawProperties, float pTimer);

    using CollisionSet = std::set< std::tuple<btCollisionObject const*, btCollisionObject const*, btPersistentManifold const*>>;
    CollisionSet lastTickCollisionPairs;

    btBroadphaseInterface* broadphase = nullptr;
    btCollisionConfiguration* collisionConfiguration = nullptr;
    btCollisionDispatcher* dispatcher = nullptr;
    btSequentialImpulseConstraintSolver* solver = nullptr;
    btDiscreteDynamicsWorld* world = nullptr;
    DebugDrawer* debugDrawer = nullptr;
};