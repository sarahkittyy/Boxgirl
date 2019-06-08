#include "Env/Systems/Render.hpp"

namespace Env::System
{

Render::Render(sf::RenderWindow* window,
			   sf::Color background)
	: mWindow(window),
	  mBackground(background)
{
}

void Render::tick()
{
	mWindow->clear(mBackground);
	//Draw all drawable entities.
	each<Env::Component::Drawable>([this](ECSX::Entity* e) {
		mWindow->draw(*(e->get<Env::Component::Drawable>()));
	});
	mWindow->display();
}

}