#include "States/Machine.hpp"

namespace State
{

Machine::Machine(sf::RenderWindow* window,
				 ResourceManager* resource,
				 State* initialState)
	: mNextState(nullptr),
	  mWindow(window),
	  mResource(resource)
{
	setState(initialState);
}

void Machine::setState(State* newState)
{
	// Reset the state
	mCurrentState.reset(newState);
	// Configure the new state.
	mCurrentState->mSetState = std::bind(&Machine::queueSetState,
										 this,
										 std::placeholders::_1);
	mCurrentState->mResource = mResource;
	mCurrentState->mWindow   = mWindow;
	// Init the state.
	mCurrentState->init();
}

void Machine::queueSetState(State* newState)
{
	mNextState = newState;
}

void Machine::update()
{
	mCurrentState->update();
	if (mNextState != nullptr)
	{
		setState(mNextState);
		mNextState = nullptr;
	}
}

}