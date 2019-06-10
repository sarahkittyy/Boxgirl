#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"
#include "ECSX/ECSX.hpp"
#include "Env/Components/Components.hpp"
#include "Graphics/AnimatedSprite.hpp"

namespace Env::System
{

/**
 * @brief Updates the boxgirl sprite of player entities
 * (ControllablePlayer, AnimatedSprite, Body)
 * 
 */
class PlayerAnimationUpdate : public ECSX::System
{
public:
	/**
	 * @brief Update all player animated sprites based on their velocity and state.
	 * 
	 */
	void tick();
};

}