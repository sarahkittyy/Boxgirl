#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "ResourceManager.hpp"

namespace State
{

class Machine;

/**
 * @brief A derivable state for use in the FSM.
 * 
 */
class State
{
public:
	/**
	 * @brief Construct the state.
	 * 
	 */
	State();

	/**
	 * @brief Destroy the state.
	 * 
	 */
	virtual ~State();

	/**
	 * @brief Used by derived states. window(), resource(), and other
	 * state globals are only initialized inside this function,
	 * and not the constructor.
	 * 
	 */
	virtual void init();

	/**
	 * @brief Called once per frame.
	 * 
	 */
	virtual void update();

protected:
	/**
	 * @brief Returns a reference to the app window.
	 * 
	 * @return sf::RenderWindow& The main application window.
	 */
	sf::RenderWindow& window();

	/**
	 * @brief Returns a reference to the main app resource manager.
	 * 
	 * @return ResourceManager& The app resource manager.
	 */
	ResourceManager& resource();

	/**
	 * @brief Changes the state of the application to a new one.
	 * 
	 * @param newState The new state to switch to.
	 */
	void setState(State* newState);

private:
	friend class Machine;   /// For configuration on setState

	/// The app window.
	sf::RenderWindow* mWindow;
	/// The app resource manager.
	ResourceManager* mResource;
	/// Function pointer to change the app state.
	std::function<void(State*)> mSetState;
};

}