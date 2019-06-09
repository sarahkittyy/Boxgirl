#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "ECSX/ECSX.hpp"
#include "Env/Components/Components.hpp"
#include "Env/Systems/GraphicalBodySync.hpp"
#include "Env/Systems/Physics.hpp"
#include "nlohmann/json.hpp"

namespace Env::Entity
{

/**
 * @brief Create a tilemap in the given entity.
 * 
 * @param entity The entity to add the tilemap components to.
 * @param resource The app resource manager
 * @param physics The physics system in the world.
 * @param map_name The name of the map in `resource/maps/`
 */
void Tilemap(ECSX::Entity* entity,
			 ResourceManager* resource,
			 System::Physics* physics,
			 std::string map_name);

}