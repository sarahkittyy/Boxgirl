#pragma once

#include <SFML/Graphics.hpp>
#include "Env/Components/Components.hpp"
#include "ResourceManager.hpp"

#include "ECSX/ECSX.hpp"

namespace Env::System
{

class Render : public ECSX::System
{
public:
	Render(sf::RenderWindow* window,
		   sf::Color background = sf::Color(127, 127, 255));

	void tick();

private:
	sf::RenderWindow* mWindow;
	sf::Color mBackground;
};

}