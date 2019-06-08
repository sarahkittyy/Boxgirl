#include "Env/Entities/Player.hpp"

namespace Env::Entities
{

void Player(ECSX::Entity* entity,
			System::Physics* physics,
			ResourceManager* resource)
{
	b2BodyDef def;
	def.type		  = b2_dynamicBody;
	def.fixedRotation = true;
	def.gravityScale  = 1.f;
	def.position	  = b2Vec2(0, 0);

	b2Body* body = entity->use<Component::Body>(
							 physics->getWorld(),
							 def)
					   ->body;

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