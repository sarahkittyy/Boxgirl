#include "Env/CollisionTracker.hpp"

namespace Env
{

std::unordered_map<b2Fixture*, CollisionTracker::CollisionData> CollisionTracker::mCollisionData;

void CollisionTracker::BeginContact(b2Contact* contact)
{
	// Get the two fixtures.
	b2Fixture* a = contact->GetFixtureA();
	b2Fixture* b = contact->GetFixtureB();

	// Add the contacting fixtures to eachother's collisiondata.
	mCollisionData[a].Collisions.push_back(b);
	mCollisionData[b].Collisions.push_back(a);
}

void CollisionTracker::EndContact(b2Contact* contact)
{
	// Get the two fixtures.
	b2Fixture* a = contact->GetFixtureA();
	b2Fixture* b = contact->GetFixtureB();

	// The collisions of the two fixtures.
	auto& ca = mCollisionData[a].Collisions;
	auto& cb = mCollisionData[b].Collisions;

	// Remove the contacting fixtures from eachother's collisiondata.
	ca.erase(std::find(ca.begin(), ca.end(), b));
	cb.erase(std::find(cb.begin(), cb.end(), a));
}

CollisionTracker::CollisionData
CollisionTracker::getCollisionData(b2Fixture* fixture)
{
	return mCollisionData[fixture];
}

}