#include "Env/Entities/Tilemap.hpp"

namespace Env::Entity
{

void Tilemap(ECSX::Entity* entity,
			 ResourceManager* resource,
			 System::Physics* physics,
			 std::string map_name)
{
	// Create & retrieve the tilemap component.
	Graphics::Tilemap* map = &(entity->use<Component::Tilemap>(resource)->tilemap);
	// Load the map
	Component::Tilemap* map_component = entity->get<Component::Tilemap>();
	map->loadFromFile("resource/maps/" + map_name + ".json", {600, 600});

	////////////////////////////
	//
	// PHYSICS
	//
	////////////////////////////
	using gbs = System::GraphicalBodySync;

	// Add a body component.
	b2BodyDef def;
	def.allowSleep	= true;
	def.type		  = b2_staticBody;
	def.position	  = b2Vec2(0, 0);
	def.fixedRotation = true;
	def.gravityScale  = 0.0f;
	b2Body* body	  = entity->use<Component::Body>(
							  physics->getWorld(), def)
					   ->body;

	// Iterate over all tiles.
	map_component->collideableTiles = map->getTiles({{"collideable", true}});
	for (auto& tile : map_component->collideableTiles)
	{
		// Get the tile position & size.
		b2Vec2 pos  = gbs::fromVector({tile.bounds.left, tile.bounds.top});
		b2Vec2 size = gbs::fromVector({tile.bounds.width / 2.f, tile.bounds.height / 2.f});
		// Get the tile properties.
		nlohmann::json props = map->getTileProperties(tile.ID);
		// Create the tile shape.
		b2PolygonShape shape;
		shape.SetAsBox(size.x, size.y, pos + size, 0);

		// Create the fixture.
		b2FixtureDef fixdef;
		fixdef.friction	= props.at("friction").get<float>();
		fixdef.isSensor	= !props.at("solid").get<bool>();
		fixdef.density	 = 1.f;
		fixdef.restitution = props.at("restitution").get<float>();
		fixdef.shape	   = &shape;
		// Store a pointer to the tile ID here.
		fixdef.userData = (void*)(&tile);
		TaggedData::tagData("Graphics::Tilemap::Tile", fixdef.userData);

		// Set the fixture.
		body->CreateFixture(&fixdef);
	}
}

}