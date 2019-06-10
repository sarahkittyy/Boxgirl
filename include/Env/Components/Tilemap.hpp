#pragma once

#include <SFML/Graphics.hpp>
#include "Graphics/Tilemap.hpp"

#include "ECSX/Component.hpp"
#include "Env/Components/Drawable.hpp"
#include "nlohmann/json.hpp"

namespace Env::Component
{

/**
 * @brief A graphical tilemap container component
 * 
 */
class Tilemap : public Env::Component::Drawable
{
public:
	/**
	 * @brief Init the tilemap component
	 * 
	 * @param resource The app resource manager.
	 */
	Tilemap(ResourceManager* resource);

	/**
	 * @brief The graphical tilemap instance.
	 * 
	 */
	Graphics::Tilemap tilemap;

	/// This component's copy of the map's collideable tiles,
	/// for storing in fixture data.
	std::vector<Graphics::Tilemap::Tile> collideableTiles;

private:
	/**
	 * @brief Draws the tilemap.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}