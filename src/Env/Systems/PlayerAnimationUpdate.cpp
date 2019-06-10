#include "Env/Systems/PlayerAnimationUpdate.hpp"

namespace Env::System
{

void PlayerAnimationUpdate::tick()
{
	each<Component::ControllablePlayer,
		 Component::Body,
		 Component::AnimatedSprite>(
		[](ECSX::Entity* entity) {
			// Get the sprite.
			Graphics::AnimatedSprite* sprite;
			sprite = &(entity->get<Component::AnimatedSprite>()->sprite);
			// Get the controllableplayer component.
			Component::ControllablePlayer* player;
			player = entity->get<Component::ControllablePlayer>();

			// Get ground collisions.
			std::vector<b2Fixture*> colliding;
			colliding = CollisionTracker::getCollisionData(player->groundFixture).Collisions;

			// Get the b2Body
			b2Body* body = entity->get<Component::Body>()->body;
			// Body velocity.
			b2Vec2 vel = body->GetLinearVelocity();
			// The direction the sprite is facing
			std::string direction = "left";
			// The action the sprite is taking.
			std::string action = "stand";

			// If our x velocity is definitively non-zero,
			// we can change the animation.
			// First, get the active direction
			std::string current_anim = sprite->getAnimation();
			if (current_anim.find("left") != std::string::npos)
			{
				direction = "left";
			}
			else
			{
				direction = "right";
			}

			//If our velocity is not near 0, change direction.
			if (std::abs(vel.x) > 0.1f)
			{
				direction = vel.x > 0 ? "right" : "left";
			}

			// If we're in air...
			if (!player->onSolidGround(colliding))
			{
				//We're jumping.
				action = "jump";
			}
			else
			{
				//If our velocity is zero..
				if (std::abs(vel.x) < 0.01f)
				{
					// Standing
					action = "stand";
				}
				else
				{
					// Walking
					action = "walk";
				}
			}

			// Set the animation.
			sprite->setAnimation(action + direction);
		});
}

}