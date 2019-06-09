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
	map->loadFromFile("resource/maps/" + map_name + ".json");

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
}

}