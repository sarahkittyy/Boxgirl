#pragma once

#include "Box2D/Box2D.h"
#include "ECSX/ECSX.hpp"
#include "Env/CollisionTracker.hpp"
#include "Env/Components/Components.hpp"

namespace Env::System
{

/**
 * @brief Holds the b2World instance,
 * and steps the physics world at a regular interval.
 * 
 */
class Physics : public ECSX::System
{
public:
	/**
	 * @brief Initializes the world.
	 * 
	 */
	Physics();

	/**
	 * @brief Updates the physics world.
	 * 
	 */
	void tick();

	/**
	 * @brief Get the world, for adding new bodies.
	 * 
	 * @return b2World* const A const pointer to the world.
	 */
	b2World* const getWorld();

private:
	/// The Box2D world.
	b2World mWorld;
	/// The Box2D contact listener.
	CollisionTracker mCollisionTracker;
	/// The timer tracking and updating the physics at fixed intervals.
	sf::Clock mPhysicsClock;
};

}