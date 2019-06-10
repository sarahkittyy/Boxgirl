#pragma once

#include <SFML/Window.hpp>
#include <cmath>
#include "Box2D/Box2D.h"
#include "ECSX/System.hpp"
#include "Env/CollisionTracker.hpp"
#include "Env/Components/Body.hpp"
#include "Env/Components/ControllablePlayer.hpp"
#include "Env/TaggedData.hpp"
#include "Graphics/Tilemap.hpp"

namespace Env::System
{

/**
 * @brief Controls all entities with a ControllablePlayer and Body component,
 * using the arrow keys.
 * 
 */
class PlayerControl : public ECSX::System
{
public:
	/**
	 * @brief Update all controllable bodies.
	 * 
	 */
	void tick();

private:
	/**
	 * @brief Apply forces to the body based on the left-right control
	 * keys.
	 * 
	 * @param body The body to apply the forces to.
	 * @param accelForce The force to push the body with. 
	 */
	void applyLRForces(b2Body* body, float accelForce);

	/**
	 * @brief Cap the body's X velocity.
	 * 
	 * @param body The body.
	 * @param xMax The maximum x velocity.
	 */
	void capXVelocity(b2Body* body, float xMax);

	/**
	 * @brief Cap the body's Y velocity.
	 * 
	 * @param body The body to cap.
	 * @param yMax The maximum y velocity.
	 */
	void capYVelocity(b2Body* body, float yMax);

	/**
	 * @brief Toggle on & off medium physics based on the currently collided-with tiles's properties.
	 * 
	 * @param medium A mutable reference to a string,
	 * will be changed to the type of medium currently in contact with.
	 * @param playerFixture The player's fixture.
	 */
	void toggleMediumPhysics(std::string& medium, b2Fixture* playerFixture);

	/**
	 * @brief Get the maximum ground friction based on all colliding ground fixtures.
	 * 
	 * @param collisions All fixtures the player is standing on. 
	 * @return float The maximum ground friction.
	 */
	float getMaxGroundFriction(std::vector<b2Fixture*> collisions);

	/**
	 * @brief Decelerate a b2Body by a given amount.
	 * 
	 * @param body The body to decelerate.
	 * @param velAmount The velocity to decelerate the body by.
	 */
	void decelerateBody(b2Body* body, float velAmount);
};

}