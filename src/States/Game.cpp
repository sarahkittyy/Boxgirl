#include "States/Game.hpp"

namespace State
{

void Game::init()
{
	// Register the render system
	mWorld.registerSystem<Env::System::Render>(&window());
}

void Game::update()
{
	//Tick the world
	mWorld.tick();
}

}