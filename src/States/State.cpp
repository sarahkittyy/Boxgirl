#include "States/State.hpp"

namespace State
{

State::State()
{
}

State::~State()
{
}

void State::init()
{
}

void State::update()
{
}

sf::RenderWindow& State::window()
{
	return *mWindow;
}

ResourceManager& State::resource()
{
	return *mResource;
}

void State::setState(State* newState)
{
	mSetState(newState);
}

}