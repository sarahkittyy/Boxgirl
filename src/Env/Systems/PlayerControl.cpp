#include "Env/Systems/PlayerControl.hpp"

namespace Env::System
{

void PlayerControl::tick()
{
	each<Component::Body, Component::ControllablePlayer>(
		[this](ECSX::Entity* entity) {
			// Get components
			b2Body* body = entity->get<Component::Body>()->body;
			Component::ControllablePlayer* control =
				entity->get<Component::ControllablePlayer>();

			// Get the collisiondata for the ground fixture.
			std::vector<b2Fixture*> colliding =
				CollisionTracker::getCollisionData(control->groundFixture).Collisions;

			// Toggles medium physics.
			toggleMediumPhysics(control->currentMedium,
								control->playerFixture);

			// Get the current set of physics.
			Component::ControllablePlayer::GeneralPhysics& physics =
				control->physics[control->currentMedium];

			// Set the gravity scale.
			body->SetGravityScale(physics.gravityScale);

			//Keyboard state aliases
			auto& KeyHit = sf::Keyboard::isKeyPressed;
			using Key	= sf::Keyboard::Key;

			//Apply left-right forces
			applyLRForces(body, physics.accelForce);
			// Cap X velocity.
			capXVelocity(body, physics.xMax);
			// Cap Y velocity.
			capYVelocity(body, physics.yMax);

			// Get the maximum ground friction
			float maxFriction = getMaxGroundFriction(colliding);

			//Decelerate the body based on the friction.
			decelerateBody(body, physics.decel * maxFriction);

			// Applies a downward force. For certain mediums
			if (KeyHit(Key::S) && physics.canDescend)
			{
				// "Jump downward"
				body->ApplyLinearImpulseToCenter(b2Vec2(0, -physics.jumpImpulse), true);
			}

			if (KeyHit(Key::W))
			{
				// If we can jump...
				if (control->canJump(colliding))
				{
					//Jump.
					body->ApplyLinearImpulseToCenter(
						b2Vec2(0, physics.jumpImpulse), true);
				}
			}
		});
}

void PlayerControl::applyLRForces(b2Body* body, float accelForce)
{

	//Keyboard State aliases
	auto& KeyHit = sf::Keyboard::isKeyPressed;
	using Key	= sf::Keyboard::Key;

	if (KeyHit(Key::A))
	{
		body->ApplyForceToCenter(b2Vec2(-accelForce, 0), true);
	}
	if (KeyHit(Key::D))
	{
		body->ApplyForceToCenter(b2Vec2(accelForce, 0), true);
	}
}

void PlayerControl::capXVelocity(b2Body* body, float xMax)
{
	b2Vec2 vel = body->GetLinearVelocity();
	if (std::abs(vel.x) > std::abs(xMax))
	{
		vel.x = xMax * (vel.x / std::abs(vel.x));
		body->SetLinearVelocity(vel);
	}
}

void PlayerControl::capYVelocity(b2Body* body, float yMax)
{
	b2Vec2 vel = body->GetLinearVelocity();
	if (std::abs(vel.y) > std::abs(yMax))
	{
		vel.y = yMax * (vel.y / std::abs(vel.y));
		body->SetLinearVelocity(vel);
	}
}

void PlayerControl::toggleMediumPhysics(std::string& medium, b2Fixture* playerFixture)
{
	medium = "air";   //Defaults to air medium
	// Get all tiles colliding with the fixture.
	for (auto& fixture : CollisionTracker::getCollisionData(playerFixture).Collisions)
	{
		// Assert it's a tile.
		if (TaggedData::getType(fixture->GetUserData()) != "Graphics::Tilemap::Tile")
		{
			continue;
		}

		// Get the tile.
		auto tile = *reinterpret_cast<Graphics::Tilemap::Tile*>(fixture->GetUserData());

		// Get the tile properties.
		nlohmann::json props = tile.map->getTileProperties(tile.ID);

		// If it's water, the medium is water, and we're done.
		if (props.at("water").get<bool>())
		{
			medium = "water";
			return;
		}
	}
}

float PlayerControl::getMaxGroundFriction(std::vector<b2Fixture*> collisions)
{
	float maxFriction = 0;
	for (auto& fixture : collisions)
	{
		// Get the fixture friction.
		float fixFriction = fixture->GetFriction();
		// If it's the maximum friction so far, set it.
		maxFriction = std::max(maxFriction, fixFriction);
	}
	return maxFriction;
}

void PlayerControl::decelerateBody(b2Body* body, float velAmount)
{
	b2Vec2 vel = body->GetLinearVelocity();
	if (vel.x > velAmount / 2.f)
	{
		vel.x -= velAmount;
	}
	else if (vel.x < -velAmount / 2.f)
	{
		vel.x += velAmount;
	}
	else
	{
		vel.x = 0;
	}

	body->SetLinearVelocity(vel);
}

}