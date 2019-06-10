#pragma once

#include <string>
#include <unordered_map>
#include "Box2D/Box2D.h"
#include "ECSX/ECSX.hpp"
#include "Env/CollisionTracker.hpp"
#include "Env/TaggedData.hpp"
#include "Graphics/Tilemap.hpp"

namespace Env::Component
{

class ControllablePlayer : public ECSX::Component
{
public:
	struct GeneralPhysics
	{
		/// The gravity scaling.
		float gravityScale;

		/// Maximum x velocity.
		float xMax;
		/// Maximum y velocity.
		float yMax;

		/// Force applied on left/right press.
		float accelForce;

		/// The velocity to decelerate by at max (1.f) friction.
		float decel;

		/// Impulse applied on a jump
		float jumpImpulse;

		/// Whether or not we can jump anywhere.
		bool canJumpAnywhere;

		/// For mediums like water, where we can descend.
		bool canDescend;
	};

	/// Defines physics in different mediums
	std::unordered_map<std::string, GeneralPhysics> physics;
	std::string currentMedium;

	/// Pointer to the player fixture, for environment sensing.
	b2Fixture* playerFixture;

	/// Pointer to the ground sensor fixture, for jumping control.
	b2Fixture* groundFixture;

	/// True if the player is able to jump.
	/// Pass a vector of fixtures colliding groundFixture
	bool canJump(std::vector<b2Fixture*> colliding);
	
	/// True if the player is on solid ground.
	/// Pass a vector of fixtures colliding groundFixture
	bool onSolidGround(std::vector<b2Fixture*> colliding);
};

}