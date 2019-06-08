#include "Application.hpp"

Application::Application()
	: mWindow(sf::VideoMode(600, 600), "Boxjump"),
	  mSM(&mWindow,
		  &mResource,
		  new State::Game())
{
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