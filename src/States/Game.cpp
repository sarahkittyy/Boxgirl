#include "States/Game.hpp"

namespace State
{

void Game::init()
{
	// Register the render system
	mWorld.registerSystem<Env::System::Render>(&window());
	mPhysicsSystem = mWorld.registerSystem<Env::System::Physics>();
	mWorld.registerSystem<Env::System::GenericUpdate>();
	mWorld.registerSystem<Env::System::GraphicalBodySync>();
	mWorld.registerSystem<Env::System::PlayerControl>();

	Env::Entity::Player(mWorld.createEntity(),
						mPhysicsSystem,
						&resource(),
						{300, 0});
	Env::Entity::Tilemap(mWorld.createEntity(),
						 &resource(),
						 mPhysicsSystem,
						 "test");
}

void Game::update()
{
	//Tick the world
	mWorld.tick();
}

}