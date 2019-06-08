#pragma once

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
};

}