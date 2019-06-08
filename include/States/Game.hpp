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
	void init();

	void update();

private:
	/// The world where all entities and systems are stored.
	ECSX::World mWorld;
};

}