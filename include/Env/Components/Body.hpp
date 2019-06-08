#pragma once

#include "Box2D/Box2D.h"
#include "ECSX/Component.hpp"

namespace Env::Component
{

/**
 * @brief Box2D body component.
 * 
 */
class Body : virtual public ECSX::Component
{
public:
	/**
	 * @brief Init the body.
	 * 
	 * @param world The world to add the body to.
	 * @param def The body definition
	 */
	Body(b2World* world,
		 b2BodyDef def);

	/// The actual Box2D body.
	b2Body* body;
};

}