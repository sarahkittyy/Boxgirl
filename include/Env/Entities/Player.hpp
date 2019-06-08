#pragma once

#include "ResourceManager.hpp"

#include "ECSX/Entity.hpp"
#include "Env/Components/Components.hpp"
#include "Env/Systems/Physics.hpp"

namespace Env::Entities
{

/**
 * @brief Create a player object.
 * 
 * @param entity The entity in the world to configure.
 * @param physics The world's physics system.
 * @param resource The app resource manager.
 */
void Player(ECSX::Entity* entity,
			System::Physics* physics,
			ResourceManager* resource);

}