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

	static void InitPhysicWorld();
	static void DestroyPhysicWorld();

	static bool RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, 
						HitResult& pOutHit, const RayCastDebug pDrawProperties = RayCastDebug::None,
						float pTimer = -1, const std::vector<GameObject*>& pIgnoredObjects = {},
						const lm::FVec3& pRayColor = { 0,1,0 }, const lm::FVec3& pHitColor = { 1, 0, 0 });

	static void AddRigidBodyInWorld(btRigidBody* pRigidBody);
	static void RemoveRigidBodyFromWorld(btRigidBody* pRigidBody);
	static void UpdatePhysics(double pDeltaTime);
	static void DrawDebug();

private:

	static void CheckCollision();
	static void TickCallBack(btDynamicsWorld* pWorld, btScalar pTimeStep);
	static void RayCastDebugDraw(const lm::FVec3& pStart, const lm::FVec3& pEnd, const lm::FVec3& pColor, const RayCastDebug& pDrawProperties, float pTimer);

	static btDiscreteDynamicsWorld* GetWorld();

	using CollisionSet = std::set< std::tuple<btCollisionObject const*, btCollisionObject const*, btPersistentManifold const*>>;
	inline static CollisionSet lastTickCollisionPairs;

	inline static btBroadphaseInterface* broadphase;
	inline static btCollisionConfiguration* collisionConfiguration;
	inline static btCollisionDispatcher* dispatcher;
	inline static btSequentialImpulseConstraintSolver* solver;
	inline static btDiscreteDynamicsWorld* world;
	inline static DebugDrawer* debugDrawer;
};