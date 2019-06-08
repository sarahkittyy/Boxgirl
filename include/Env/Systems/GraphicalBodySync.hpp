#pragma once

#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h"

#include "ECSX/System.hpp"

#include "Env/Components/Components.hpp"

namespace Env::System
{

/**
 * @brief Synchronizes graphical bodies with their Box2D bodies.
 * 
 */
class GraphicalBodySync : public ECSX::System
{
public:
	void tick();

private:
	/// Transform from Box2D to graphical.
	const float SCALE = 20.f;
};

}