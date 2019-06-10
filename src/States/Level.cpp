#include "States/Level.hpp"

namespace State
{

Level::Level(int level)
	: mCurrentLevel(level)
{
}

void Level::init()
{
	// Register the render system
	mWorld.registerSystem<Env::System::Render>(&window());
	mPhysicsSystem = mWorld.registerSystem<Env::System::Physics>();
	mWorld.registerSystem<Env::System::GenericUpdate>();
	mWorld.registerSystem<Env::System::GraphicalBodySync>();
	mWorld.registerSystem<Env::System::PlayerControl>();
	mWorld.registerSystem<Env::System::PlayerAnimationUpdate>();

	Env::Entity::Player(mWorld.createEntity(),
						mPhysicsSystem,
						&resource(),
						{300, 0});
	Env::Entity::Tilemap(mWorld.createEntity(),
						 &resource(),
						 mPhysicsSystem,
						 "levels/" + std::to_string(mCurrentLevel));
}

void Level::update()
{
	//Tick the world
	mWorld.tick();
}

}