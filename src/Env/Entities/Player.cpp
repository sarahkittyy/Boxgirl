#include "Env/Entities/Player.hpp"

namespace Env::Entities
{

void Player(ECSX::Entity* entity,
			System::Physics* physics,
			ResourceManager* resource)
{
	// Create the physics body.
	b2BodyDef def;
	def.type		  = b2_dynamicBody;
	def.fixedRotation = true;
	def.gravityScale  = 1.f;
	def.position	  = b2Vec2(0, 0);
	b2Body* body	  = entity->use<Component::Body>(
							  physics->getWorld(),
							  def)
					   ->body;

	using gbs = System::GraphicalBodySync;

	b2ChainShape playerShape;
	b2Vec2 vertices[4];
	vertices[0] = gbs::fromVector({0, 0});
	vertices[1] = gbs::fromVector({0, 28});
	vertices[2] = gbs::fromVector({18, 28});
	vertices[3] = gbs::fromVector({18, 0});
	playerShape.CreateChain(vertices, 4);

	//Create the fixtures
	b2FixtureDef player;
	player.density	 = 1.f;
	player.friction	= 0.2f;
	player.restitution = 0.f;
	player.isSensor	= false;
	player.shape	   = &playerShape;
	body->CreateFixture(&player);

	//Create the animated sprite.
	Graphics::AnimatedSprite& spr = entity->use<Component::AnimatedSprite>()->sprite;

	spr.texture(resource->texture("resource/sprites/boxgirl.png"))
		.frameSize({18, 28})
		.renderSize({18, 28})
		.init();
	spr.addAnimation("default", {.frames = {0, 1, 2, 3, 4, 5}, .speed = sf::seconds(0.2f)});
	spr.setAnimation("default");
	spr.start();
}

}