#pragma once

#include "ECSX/System.hpp"
#include "Env/Components/Components.hpp"

namespace Env::System
{

/**
 * @brief Updates all GenericUpdateable components each tick.
 * 
 */
class GenericUpdate : public ECSX::System
{
public:
	/**
	 * @brief Update all genericUpdateable components.
	 * 
	 */
	void tick();
};

}