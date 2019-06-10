#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(600, 600), "Boxgirl"),
	  mSM(&mWindow,
		  &mResource,
		  new State::Level(1))
{
	// Load the icon.
	sf::Image icon;
	icon.loadFromFile("resource/icon.png");
	mWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

int Application::run()
{
	while (mWindow.isOpen())
	{
		//Poll events
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			switch (event.type)
			{
			default:
				break;
			case sf::Event::Closed:
				mWindow.close();
				break;
			}
		}

		//Update the state machine.
		mSM.update();
	}
	return 0;
}