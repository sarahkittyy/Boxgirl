#include "Env/Entities/Player.hpp"

namespace Env::Entity
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

	//Center and move the transformable container over the sprite.
	using gbs = System::GraphicalBodySync;
	gbs::orientCenter(&spr);
	spr.setPosition({0, 0});
	entity->get<Component::AnimatedSprite>()->setPosition(initial_pos);

	// Add the controllable component
	Component::ControllablePlayer* control = entity->use<Component::ControllablePlayer>();

	control->physics["air"].accelForce		= 3.f;
	control->physics["air"].decel			= 0.1f;
	control->physics["air"].xMax			= 12.f;
	control->physics["air"].jumpImpulse		= -28.f;
	control->physics["air"].canJumpAnywhere = false;
	control->physics["air"].gravityScale	= 8.f;
	control->physics["air"].yMax			= 20.f;
	control->physics["air"].canDescend		= false;

	control->physics["water"].accelForce	  = 2.5f;
	control->physics["water"].decel			  = 0.05f;
	control->physics["water"].xMax			  = 4.f;
	control->physics["water"].jumpImpulse	 = -0.05f;
	control->physics["water"].canJumpAnywhere = true;
	control->physics["water"].gravityScale	= 0.5f;
	control->physics["water"].yMax			  = 12.f;
	control->physics["water"].canDescend	  = true;

	control->currentMedium = "air";

	// Create the physics body.
	b2BodyDef def;
	def.type		  = b2_dynamicBody;
	def.fixedRotation = true;
	def.linearDamping = 1.f;
	def.gravityScale  = 8.f;
	def.position	  = gbs::fromVector(initial_pos);
	b2Body* body	  = entity->use<Component::Body>(
							  physics->getWorld(),
							  def)
					   ->body;

	// Player fixtures
	b2ChainShape playerShape;
	b2Vec2 vertices[4];
	sf::Vector2f playerSize = gbs::halfSize(spr);

	vertices[0] = gbs::fromVector({-playerSize.x, -playerSize.y});
	vertices[1] = gbs::fromVector({-playerSize.x, playerSize.y});
	vertices[2] = gbs::fromVector(playerSize);
	vertices[3] = gbs::fromVector({playerSize.x, -playerSize.y});
	playerShape.CreateLoop(vertices, 4);

	// Create the fixtures
	b2FixtureDef player;
	player.density		 = 1.f;
	player.friction		 = 0.0f;
	player.restitution   = 0.f;
	player.isSensor		 = false;
	player.shape		 = &playerShape;
	b2Fixture* playerFix = body->CreateFixture(&player);

	b2PolygonShape groundShape;
	groundShape.SetAsBox((playerSize.x - 1.f) * gbs::invscale(),
						 1.f * gbs::invscale(),
						 gbs::fromVector({0, playerSize.y}),
						 0);

	b2FixtureDef ground;
	ground.isSensor		 = true;
	ground.shape		 = &groundShape;
	b2Fixture* groundFix = body->CreateFixture(&ground);

	control->groundFixture = groundFix;
	control->playerFixture = playerFix;
}

}