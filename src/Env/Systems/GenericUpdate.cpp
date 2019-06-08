#include "Env/Systems/GenericUpdate.hpp"

namespace Env::System
{

void GenericUpdate::tick()
{
	//Upate all updateable components.
	each<Env::Component::GenericUpdateable>([](ECSX::Entity* e) {
		e->get<Env::Component::GenericUpdateable>()->update();
	});
}

}