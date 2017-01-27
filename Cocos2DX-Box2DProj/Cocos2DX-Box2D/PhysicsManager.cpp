#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{
	world = new b2World(gravity);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags +=b2Draw::e_aabbBit;
	flags += b2Draw::e_centerOfMassBit;
	debugDraw = new GLESDebugDraw(SCALE_RATIO);
	debugDraw->AppendFlags(flags);

	world->SetDebugDraw(debugDraw);
}

PhysicsManager::~PhysicsManager()
{
	b2Body* body = world->GetBodyList();

	for (int b = 0; b < world->GetBodyCount(); b++)
	{
		b2Body* bodyb = &body[b];
		if (bodyb) world->DestroyBody(bodyb);
	}
	delete world;

	delete debugDraw;
}

void PhysicsManager::Update()
{
	int positionIterations = 5;
	int velocityIterations = 1;

	world->Step(1.0 / 60.0, positionIterations, velocityIterations);

	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		if (body->GetUserData() != nullptr)
		{
		}
	}
}

void PhysicsManager::RenderDebug()
{
	world->DrawDebugData();
}
