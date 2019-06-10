#pragma once

#include <string>
#include "ECSX/ECSX.hpp"
#include "Env/Env.hpp"
#include "States/State.hpp"

namespace State
{

/**
 * @brief Loads and plays a level..
 * 
 */
class Level : public State
{
public:
	/**
	 * @brief Loads the leve.
	 * 
	 * @param level The level number.
	 */
	Level(int level);

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
	/// The current level we are playing.
	const int mCurrentLevel;

	/// The world where all entities and systems are stored.
	ECSX::World mWorld;

	////////////////////////////
	//
	// ECSX System pointers.
	//
	////////////////////////////
	Env::System::Physics* mPhysicsSystem;
};

}