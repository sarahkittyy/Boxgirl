#pragma once

#include "ECSX/Component.hpp"

namespace Env::Component
{

/**
 * @brief Defines entities with a generic update() that needs no
 * parameters.
 * 
 */
class GenericUpdateable : virtual public ECSX::Component
{
public:
	/**
	 * @brief Virtual DTOR
	 * 
	 */
	virtual ~GenericUpdateable();

	/**
	 * @brief Inherited by derived components, updates the component.
	 * 
	 */
	virtual void update() = 0;
};

}