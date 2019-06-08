#include "Env/Components/AnimatedSprite.hpp"

namespace Env::Component
{

void AnimatedSprite::update()
{
	//Update the animated sprite.
	sprite.update();
}

void AnimatedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(sprite, states);
}

}