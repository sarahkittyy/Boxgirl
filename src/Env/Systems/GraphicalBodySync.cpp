#include "Env/Systems/GraphicalBodySync.hpp"

namespace Env::System
{

void GraphicalBodySync::tick()
{
	each<Env::Component::Body, Env::Component::Transformable>(
		[this](ECSX::Entity* e) {
			Env::Component::Body* body				 = e->get<Env::Component::Body>();
			Env::Component::Transformable* transform = e->get<Env::Component::Transformable>();

			b2Vec2 body_pos = body->body->GetPosition();
			body_pos *= SCALE;
			transform->setPosition(body_pos.x, body_pos.y);
		});
}

}