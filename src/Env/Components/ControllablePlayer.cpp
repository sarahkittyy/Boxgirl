#include "Env/Components/ControllablePlayer.hpp"

namespace Env::Component
{

bool ControllablePlayer::canJump(std::vector<b2Fixture*> colliding)
{
	//Get the body from the fixture
	b2Body* body = playerFixture->GetBody();

	//True if there's nothing but non-solid tiles below us. (fake collision)
	// There is a valid floor immediately if
	// physics.canJumpAnywhere is true
	bool noValidFloor = !onSolidGround(colliding) && !physics[currentMedium].canJumpAnywhere;


	// If there's valid floor
	// (And we're not vertically moving..)
	// ..we can jump
	return (!noValidFloor && (std::abs(body->GetLinearVelocity().y) < 0.01f || physics[currentMedium].canJumpAnywhere));
}

bool ControllablePlayer::onSolidGround(std::vector<b2Fixture*> colliding)
{
	// Get only all tile types from colliding fixtures.
	std::vector<Graphics::Tilemap::Tile> tiles_colliding;
	for (auto& fixture : colliding)
	{
		if (TaggedData::getType(fixture->GetUserData()) == "Graphics::Tilemap::Tile")
		{
			tiles_colliding.push_back(
				*reinterpret_cast<Graphics::Tilemap::Tile*>(fixture->GetUserData()));
		}
	}

	// Made false when a solid floor is found.
	bool noValidFloor = true;

	// If there are any non-tile-collisions,
	// there's valid floor.
	if (tiles_colliding.size() < colliding.size())
	{
		noValidFloor = false;
	}

	//Iterate over all tile collisions..
	for (auto& tile : tiles_colliding)
	{
		// For any earlier conditions
		if (!noValidFloor)
		{
			break;
		}

		//If the tile is solid, we're fine.

		if (tile.map->getTileProperties(tile.ID).at("solid").get<bool>())
		{
			noValidFloor = false;
			break;
		}
	}

	return !noValidFloor;
}

}