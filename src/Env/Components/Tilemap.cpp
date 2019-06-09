#include "Env/Components/Tilemap.hpp"

namespace Env::Component
{

Tilemap::Tilemap(ResourceManager* resource)
	: tilemap(resource)
{
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(tilemap, states);
}

}