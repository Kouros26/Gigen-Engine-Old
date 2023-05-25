#include "WorldPhysics.h"
#include <algorithm>
#include "DrawLine.h"
#include "RigidBody.h"

Collision::Collision(GameObject* pOther, const btManifoldPoint pManifold)
    : other(pOther)
{
    const btVector3 position = pManifold.getPositionWorldOnA();

    contactPoint = { position.x(), position.y(), position.z() };
    collisionStrength = pManifold.getAppliedImpulse();
}

void WorldPhysics::InitPhysicWorld()
{
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver();
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    debugDrawer = new DebugDrawer(1);
    world->setGravity(btVector3(0, -9.81f, 0));
    world->setDebugDrawer(debugDrawer);

    world->setInternalTickCallback(TickCallBack, world);
}

void WorldPhysics::DestroyPhysicWorld() const
{
    delete world;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;
    delete debugDrawer;
}

void WorldPhysics::ClearCollisionCache()
{
    lastTickCollisionPairs.clear();
}

bool WorldPhysics::RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit, RayCastDebug pDrawProperties, float pTimer, const std::vector<GameObject*>& pIgnoredObjects, const lm::FVec3& pRayColor, const lm::FVec3& pHitColor)
{
    const btVector3 rayFrom(pStart.x, pStart.y, pStart.z);
    const btVector3 rayTo(pEnd.x, pEnd.y, pEnd.z);

    btCollisionWorld::AllHitsRayResultCallback rayCallback(rayFrom, rayTo);

    GetInstance().world->rayTest(rayFrom, rayTo, rayCallback);

    //if no hits draw hitless line
    if (!rayCallback.hasHit())
    {
        RayCastDebugDraw(pStart, pEnd, pRayColor, pDrawProperties, pTimer);

        return false;
    }

    //for each object hit by ray
    for (int i = 0; i < rayCallback.m_collisionObjects.size(); i++)
    {
        const auto body = const_cast<btRigidBody*>(btRigidBody::upcast(rayCallback.m_collisionObject));

        lm::FVec3 nextObj = { rayCallback.m_hitPointWorld[i].x(), rayCallback.m_hitPointWorld[i].y(), rayCallback.m_hitPointWorld[i].z() };

        //draw hitless line from camera to first object
        if (i == 0)
            RayCastDebugDraw(pStart, nextObj, pRayColor, pDrawProperties, pTimer);

        //draw hitless line from last obj to next obj
        else
        {
            lm::FVec3 hitIgnoredObj = { rayCallback.m_hitPointWorld[i - 1].x(), rayCallback.m_hitPointWorld[i - 1].y(), rayCallback.m_hitPointWorld[i - 1].z() };
            RayCastDebugDraw(hitIgnoredObj, nextObj, pRayColor, pDrawProperties, pTimer);
        }

        //check if current object should be ignored
        for (const auto ignoredObject : pIgnoredObjects)
        {
            //if it shouldn't be ignored and isn't kinematic draw hitfull line until end
            if (!(body->getUserPointer() == ignoredObject) && !body->isKinematicObject())
            {
                pOutHit.hitObject = static_cast<GameObject*>(body->getUserPointer());
                pOutHit.hitPoint = nextObj;

                RayCastDebugDraw(pOutHit.hitPoint, pEnd, pHitColor, pDrawProperties, pTimer);

                return true;
            }
        }
    }
    return false;
}

bool WorldPhysics::RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit, const RayCastDebug pDrawProperties, float pTimer, const lm::FVec3& pRayColor)
{
    return SimpleRayCast(pStart, pEnd, pOutHit, pDrawProperties, pTimer, pRayColor);
}

bool WorldPhysics::SimpleRayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit,
    const RayCastDebug pDrawProperties, float pTimer, const lm::FVec3& pRayColor)
{
    const btVector3 rayFrom(pStart.x, pStart.y, pStart.z);
    const btVector3 rayTo(pEnd.x, pEnd.y, pEnd.z);

    btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom, rayTo);

    GetInstance().world->rayTest(rayFrom, rayTo, rayCallback);

    if (!rayCallback.hasHit())
    {
        RayCastDebugDraw(pStart, pEnd, pRayColor, pDrawProperties, pTimer);

        return false;
    }

    const auto body = const_cast<btRigidBody*>(btRigidBody::upcast(rayCallback.m_collisionObject));
    const lm::FVec3 nextObj = { rayCallback.m_hitPointWorld.x(), rayCallback.m_hitPointWorld.y(), rayCallback.m_hitPointWorld.z() };

    pOutHit.hitObject = static_cast<GameObject*>(body->getUserPointer());
    pOutHit.hitPoint = nextObj;

    RayCastDebugDraw(pStart, pOutHit.hitPoint, pRayColor, pDrawProperties, pTimer);

    return true;
}

bool WorldPhysics::RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit, const RayCastDebug pDrawProperties /*= RayCastDebug::None*/, float pTimer /*= -1*/, const lm::FVec3& pRayColor /*= { 0,1,0 }*/, const lm::FVec3& pHitColor /*= { 1, 0, 0 }*/)
{
    std::vector<GameObject*> emptyVector;
    return RayCast(pStart, pEnd, pOutHit, pDrawProperties, pTimer, emptyVector, pRayColor, pHitColor);
}

bool WorldPhysics::RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit, const RayCastDebug pDrawProperties, float pTimer)
{
    return SimpleRayCast(pStart, pEnd, pOutHit, pDrawProperties, pTimer, { 0,1,0 });
}

bool WorldPhysics::RayCast(const lm::FVec3& pStart, const lm::FVec3& pEnd, HitResult& pOutHit)
{
    std::vector<GameObject*> emptyVector;
    return RayCast(pStart, pEnd, pOutHit, RayCastDebug::None, -1, emptyVector);
}

void WorldPhysics::AddRigidBodyInWorld(btRigidBody& pRigidBody) const
{
    world->addRigidBody(&pRigidBody);
}

void WorldPhysics::RemoveRigidBodyFromWorld(btRigidBody& pRigidBody) const
{
    for (int i = 0; i < pRigidBody.getNumConstraintRefs(); i++)
        GetInstance().GetWorld()->removeConstraint(pRigidBody.getConstraintRef(i));

    world->removeRigidBody(&pRigidBody);
}

void WorldPhysics::UpdatePhysics(double pDeltaTime) const
{
    world->stepSimulation(static_cast<float>(pDeltaTime));
}

void WorldPhysics::DrawDebug() const
{
    world->debugDrawWorld();
}

void WorldPhysics::CheckCollision()
{
    if (!dispatcher)
        return;

    CollisionSet newCollisions;

    for (int i = 0; i < dispatcher->getNumManifolds(); ++i)
    {
        btPersistentManifold* manifold = dispatcher->getManifoldByIndexInternal(i);
        if (manifold == nullptr || manifold->getNumContacts() <= 0)
            continue;

        const btCollisionObject* body0 = manifold->getBody0();
        const btCollisionObject* body1 = manifold->getBody1();

        if (body0 > body1)
            std::swap(body0, body1);

        newCollisions.emplace(body0, body1, manifold);
    }

    CollisionSet differenceSet;
    std::ranges::set_symmetric_difference(lastTickCollisionPairs, newCollisions,
        std::inserter(differenceSet, differenceSet.begin()));

    unsigned int i = 0;
    for (std::tuple<const btCollisionObject*, const btCollisionObject*, const btPersistentManifold*> const& pair : differenceSet)
    {
        if (!lastTickCollisionPairs.contains(pair))
        {
            //new collision
            const auto go0 = static_cast<GameObject*>(std::get<0>(pair)->getUserPointer());
            const auto go1 = static_cast<GameObject*>(std::get<1>(pair)->getUserPointer());

            if (!go0 || !go1)
                continue;

            const auto tmp0 = go0->GetRigidBody();
            const auto tmp1 = go1->GetRigidBody();
            const CollisionCallBacks* callBacks = tmp0->GetCallBacks();
            const CollisionCallBacks* callBacks2 = tmp1->GetCallBacks();

            const btPersistentManifold* tempInfo = std::get<2>(pair);

            if (callBacks->onEnter)
                callBacks->onEnter(Collision(go1, tempInfo->getContactPoint(i)));

            if (callBacks2->onEnter)
                callBacks2->onEnter(Collision(go0, tempInfo->getContactPoint(i)));
        }

        else
        {
            //collision end
            const auto go0 = static_cast<GameObject*>(std::get<0>(pair)->getUserPointer());
            const auto go1 = static_cast<GameObject*>(std::get<1>(pair)->getUserPointer());

            if (!go0 || !go1)
                continue;

            const auto tmp0 = go0->GetRigidBody();
            const auto tmp1 = go1->GetRigidBody();
            const CollisionCallBacks* callBacks = tmp0->GetCallBacks();
            const CollisionCallBacks* callBacks2 = tmp1->GetCallBacks();

            const btPersistentManifold* tempInfo = std::get<2>(pair);

            if (callBacks->onExit)
                callBacks->onExit(Collision(go1, {}));

            if (callBacks2->onExit)
                callBacks2->onExit(Collision(go0, {}));
        }
        ++i;
    }

    lastTickCollisionPairs = newCollisions;
}

void WorldPhysics::TickCallBack(btDynamicsWorld* pWorld, btScalar pTimeStep)
{
    GetInstance().CheckCollision();
}

void WorldPhysics::RayCastDebugDraw(const lm::FVec3& pStart, const lm::FVec3& pEnd, const lm::FVec3& pColor, const RayCastDebug& pDrawProperties, float pTimer)
{
    switch (pDrawProperties)
    {
    case RayCastDebug::None:
        break;

    case RayCastDebug::OneFrame:
        Lines::DrawLine(pStart, pEnd, pColor, 0);
        break;

    case RayCastDebug::Timer:
        Lines::DrawLine(pStart, pEnd, pColor, pTimer);
        break;

    case RayCastDebug::Forever:
        Lines::DrawLine(pStart, pEnd, pColor, 3600);
        break;
    }
}

btDiscreteDynamicsWorld* WorldPhysics::GetWorld()
{
    return world;
}

WorldPhysics& WorldPhysics::GetInstance()
{
    static WorldPhysics physics;

    return physics;
}