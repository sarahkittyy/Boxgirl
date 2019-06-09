#include "Env/Entities/Player.hpp"

namespace Env::Entities
{

void Player(ECSX::Entity* entity,
			System::Physics* physics,
			ResourceManager* resource,
			sf::Vector2f initial_pos)
{
	//Create the animated sprite.
	Graphics::AnimatedSprite& spr = entity->use<Component::AnimatedSprite>()->sprite;

	spr.texture(resource->texture("resource/sprites/boxgirl.png"))
		.frameSize({18, 28})
		.renderSize({18, 28})
		.init();
	spr.addAnimation("default", {.frames = {0, 1, 2, 3, 4, 5}, .speed = sf::seconds(0.2f)});
	spr.setAnimation("default");
	spr.start();

	//Center and move the sprite.
	using gbs = System::GraphicalBodySync;
	gbs::orientCenter(&spr);
	spr.setPosition(initial_pos);

	// Create the physics body.
	b2BodyDef def;
	def.type		  = b2_dynamicBody;
	def.fixedRotation = true;
	def.gravityScale  = 1.f;
	def.position	  = gbs::fromVector(initial_pos);
	b2Body* body	  = entity->use<Component::Body>(
							  physics->getWorld(),
							  def)
					   ->body;

	b2ChainShape playerShape;
	b2Vec2 vertices[4];
	sf::Vector2f playerSize = gbs::halfSize(spr);

	vertices[0] = gbs::fromVector({-playerSize.x, -playerSize.y});
	vertices[1] = gbs::fromVector({-playerSize.x, playerSize.y});
	vertices[2] = gbs::fromVector(playerSize);
	vertices[3] = gbs::fromVector({playerSize.x, -playerSize.y});
	playerShape.CreateChain(vertices, 4);

	//Create the fixtures
	b2FixtureDef player;
	player.density	 = 1.f;
	player.friction	= 0.2f;
	player.restitution = 0.f;
	player.isSensor	= false;
	player.shape	   = &playerShape;
	body->CreateFixture(&player);
}

}