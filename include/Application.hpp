#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

#include "States/States.hpp"

/**
 * @brief Stores all application data.
 * 
 */
class Application
{
public:
	/**
	 * @brief Initialize the application
	 * 
	 */
	Application();

	/**
	 * @brief Called from main, starts the game loop.
	 * 
	 * @return int The program's exit code.
	 */
	int run();

private:
	/// App window
	sf::RenderWindow mWindow;

	/// App resource manager.
	ResourceManager mResource;

	/// The main app state machine.
	State::Machine mSM;
};