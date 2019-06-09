#include "Env/Systems/GraphicalBodySync.hpp"

namespace Env::System
{

void GraphicalBodySync::tick()
{
	each<Env::Component::Body, Env::Component::Transformable>(
		[](ECSX::Entity* e) {
			//Grab the two components
			Env::Component::Body* body				 = e->get<Env::Component::Body>();
			Env::Component::Transformable* transform = e->get<Env::Component::Transformable>();

			// Scale the body position
			sf::Vector2f graphical_pos = toVector(body->body->GetPosition());
			transform->setPosition(graphical_pos);
		});
}

////////////////////////////
//
// Graphical Scaling Methods
//
////////////////////////////

constexpr float GraphicalBodySync::SCALE;

const float GraphicalBodySync::scale()
{
	return SCALE;
}

const float GraphicalBodySync::invscale()
{
	return 1.f / SCALE;
}

b2Vec2 GraphicalBodySync::fromVector(sf::Vector2f in, bool scaleCoords)
{
	b2Vec2 ret;   // return vector
	ret.x = in.x * (scaleCoords ? invscale() : 1);
	ret.y = in.y * (scaleCoords ? invscale() : 1);
	return ret;
}

sf::Vector2f GraphicalBodySync::toVector(b2Vec2 in, bool scaleCoords)
{
	sf::Vector2f v;   //return vector.
	v.x = in.x * (scaleCoords ? scale() : 1);
	v.y = in.y * (scaleCoords ? scale() : 1);
	return v;
}

}