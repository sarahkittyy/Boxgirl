#pragma once

#include <SFML/Graphics.hpp>
#include "ECSX/Component.hpp"

namespace Env::Component
{

/**
 * @brief Virtual transformable class, for transformable SFML sprites.
 * 
 */
class Transformable : virtual public ECSX::Component, public sf::Transformable
{
public:
	/**
	 * @brief Virtual DTOR
	 * 
	 */
	virtual ~Transformable();
};

}