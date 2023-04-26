#include "DebugDrawer.h"
#include "DrawLine.h"

void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance,
	int lifeTime, const btVector3& color)
{
}

void DebugDrawer::reportErrorWarning(const char* warningString)
{
}

void DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
}

void DebugDrawer::setDebugMode(int debugMode)
{
	DebugFlags = debugMode;
}

int DebugDrawer::getDebugMode() const
{
	return DebugFlags;
}

void DebugDrawer::clearLines()
{

}

void DebugDrawer::flushLines()
{

}

DebugDrawer::DebugDrawer(int debugDrawModes) :
	DebugFlags(debugDrawModes)
{

}

DebugDrawer::~DebugDrawer()
{
}

void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	Lines::DrawLine({ from.x(), from.y(), from.z() }, { to.x(), to.y(), to.z() }, { color.x(), color.y(), color.z() }, 0);
}