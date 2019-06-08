#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

#include "ECSX/Component.hpp"

namespace Env::Component
{

/**
 * @brief An inheritable drawable component,
 * for use in the Render system.
 * 
 */
class Drawable : virtual public ECSX::Component,
				 public sf::Drawable
{
public:
	/**
	 * @brief Virtual DTOR
	 * 
	 */
	virtual ~Drawable();

private:
	/**
	 * @brief SFML's draw() override.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

}