#pragma once

#include "Box2D/Box2D.h"
#include "ECSX/ECSX.hpp"
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
	Physics();

	void tick();

	b2World* const getWorld();

private:
	/// The Box2D world.
	b2World mWorld;

	/// The timer tracking and updating the physics at fixed intervals.
	sf::Clock mPhysicsClock;
};

}