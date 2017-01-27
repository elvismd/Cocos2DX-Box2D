#pragma once

#include "Box2D/Box2D.h"
#include "GLES-Render.h"

//std
#include <vector>
#include <map>


#define SCALE_RATIO 64.0

using std::map;
using std::vector;

class PhysicsManager
{
	b2World* world;
	b2Vec2 gravity = b2Vec2(0, -9.8f);
	GLESDebugDraw* debugDraw;

public:
	PhysicsManager();
	~PhysicsManager();

	void Update();
	void RenderDebug();

	b2World* GetWorld() { return world; }

};
