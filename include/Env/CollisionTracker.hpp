#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

#include "Box2D/Box2D.h"

namespace Env
{

/**
 * @brief Tracks when collisions happen and stores them statically
 * so that a fixture's collisions can be tracked at any time.
 * 
 */
class CollisionTracker : public b2ContactListener
{
public:
	/**
	 * @brief The collision data of a fixture.
	 * 
	 */
	struct CollisionData
	{
		std::vector<b2Fixture*> Collisions;
	};

	/**
	 * @brief Called by Box2D on the start of a contact.
	 * 
	 */
	void BeginContact(b2Contact* contact);

	/**
	 * @brief Called by Box2D on the end of a contact.
	 * 
	 */
	void EndContact(b2Contact* contact);

	/**
	 * @brief Get the Collision Data of a given fixture.
	 * 
	 * @param fixture The fixture.
	 * @return CollisionData The collision data of that fixture.
	 */
	static CollisionData getCollisionData(b2Fixture* fixture);

private:
	/// Tracked data for all fixture contacts.
	static std::unordered_map<b2Fixture*, CollisionData> mCollisionData;
};

}