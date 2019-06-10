#include "Env/Systems/Physics.hpp"

namespace Env::System
{

Physics::Physics()
	: mWorld(b2Vec2(0, 9.8f))
{
	mPhysicsClock.restart();
	//Init the contact listener.
	mWorld.SetContactListener(&mCollisionTracker);
}

void Physics::tick()
{
	// Step the world 60 times / second.
	if (mPhysicsClock.getElapsedTime() > sf::milliseconds(1000.f / 60.f))
	{
		mPhysicsClock.restart();
		mWorld.Step(1.f / 60.f, 8, 3);
	}
}

b2World* const Physics::getWorld()
{
	return &mWorld;
}

}