#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include "ResourceManager.hpp"

#include "States/State.hpp"

namespace State
{

/**
 * @brief Manages, configures and updates state machine states.
 * 
 */
class Machine
{
public:
	/**
	 * @brief Initialize the state machine
	 * 
	 * @param window The app window
	 * @param resource The app resource manager
	 * @param initialState The machine's initial state.
	 */
	Machine(sf::RenderWindow* window,
			ResourceManager* resource,
			State* initialState);

	/**
	 * @brief Set the state of the machine.
	 * 
	 * @param newState The new machine's state.
	 */
	void setState(State* newState);

	/**
	 * @brief Update the current state.
	 * 
	 */
	void update();

private:
	/// The machine's current state.
	std::shared_ptr<State> mCurrentState;
	/// Stored on setState(), to only change the state
	/// after mCurrentState->update() has ran.
	State* mNextState;
	/// Called from inside states, to change the state
	/// without interrupting the flow inside mCurrentState->update()
	void queueSetState(State* newState);
	/// App window
	sf::RenderWindow* mWindow;
	/// App resource manager
	ResourceManager* mResource;
};

}