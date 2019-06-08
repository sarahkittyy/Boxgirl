#include "Env/Components/Body.hpp"

namespace Env::Component
{

Body::Body(b2World* world, b2BodyDef def)
{
	//Create the body.
	body = world->CreateBody(&def);
}

}