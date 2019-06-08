#pragma once

#include <SFML/Graphics.hpp>
#include "Env/Components/Components.hpp"
#include "ResourceManager.hpp"

#include "ECSX/ECSX.hpp"

namespace Env::System
{

/**
 * @brief A system that renders all drawable entities.
 * 
 */
class Render : public ECSX::System
{
public:
	/**
	 * @brief Initializes the render system.
	 * 
	 * @param window The window to draw to.
	 * @param background The background color to clear with.
	 */
	Render(sf::RenderWindow* window,
		   sf::Color background = sf::Color(127, 127, 255));

	/**
	 * @brief Clears the window, drawing all drawable entities.
	 * 
	 */
	void tick();

private:
	/// Pointer to the main app window.
	sf::RenderWindow* mWindow;
	/// The color to clear the window with.
	sf::Color mBackground;
};

}