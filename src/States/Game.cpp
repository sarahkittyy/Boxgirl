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

	Env::Entities::Player(mWorld.createEntity(), mPhysicsSystem, &resource());
}

void Game::update()
{
	//Tick the world
	mWorld.tick();
}

}