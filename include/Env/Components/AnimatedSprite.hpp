#pragma once

#include <SFML/Graphics.hpp>
#include "ECSX/Component.hpp"
#include "Env/Components/Drawable.hpp"
#include "Env/Components/GenericUpdateable.hpp"
#include "Env/Components/Transformable.hpp"
#include "Graphics/AnimatedSprite.hpp"

namespace Env::Component
{

/**
 * @brief Component container over a graphic AnimatedSprite instance.
 * 
 */
class AnimatedSprite : public Drawable,
					   public Transformable,
					   public GenericUpdateable
{
public:
	/// The sprite itself.
	Graphics::AnimatedSprite sprite;

	/**
	 * @brief Updates the animated sprite (GenericUpdateable)
	 * 
	 */
	void update();

private:
	/**
	 * @brief Draws the sprite.
	 * 
	 */
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}