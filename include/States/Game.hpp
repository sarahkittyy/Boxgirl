#pragma once

#include "ECSX/ECSX.hpp"
#include "Env/Env.hpp"
#include "States/State.hpp"

namespace State
{

/**
 * @brief Main boxjump game state.
 * 
 */
class Game : public State
{
public:
	/**
	 * @brief Initializes the state.
	 * 
	 */
	void init();

	/**
	 * @brief Ticks the world.
	 * 
	 */
	void update();

private:
	/// The world where all entities and systems are stored.
	ECSX::World mWorld;
};

}