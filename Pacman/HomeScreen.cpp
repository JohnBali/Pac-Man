#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "HomeScreen.h"

void HomeScreen::Show(sf::RenderWindow &renderWindow)
{
	sf::Texture homeImage;
	if (homeImage.loadFromFile("assets/homeScreen.png") != true)
	{
		return;
	}

	sf::Sprite sprite(homeImage);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed
				|| event.type == sf::Event::EventType::MouseButtonPressed
				|| event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
}