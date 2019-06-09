#pragma once

#include "ResourceManager.hpp"

#include "ECSX/Entity.hpp"
#include "Env/Components/Components.hpp"
#include "Env/Systems/GraphicalBodySync.hpp"
#include "Env/Systems/Physics.hpp"

namespace Env::Entity
{

/**
 * @brief Create a player object.
 * 
 * @param entity The entity in the world to configure.
 * @param physics The world's physics system.
 * @param resource The app resource manager.
 * @param initial_pos The initial player position.
 */
void Player(ECSX::Entity* entity,
			System::Physics* physics,
			ResourceManager* resource,
			sf::Vector2f initial_pos = {0, 0});

}