#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "FinishScreen.h"

std::string FinishScreen::Show(sf::RenderWindow &window, std::string finString, GameObjectManager &gameObjectManager)
{
	// Declare and load a font
	sf::Font font;
	sf::Vector2f pos;
	pos.x = 139;
	pos.y = 264;
	font.loadFromFile("assets/8-BIT WONDER.ttf");
	// Create a text
	sf::Text textLineOne(finString, font);
	textLineOne.setCharacterSize(26);
	textLineOne.setStyle(sf::Text::Bold);
	textLineOne.setColor(sf::Color::Red);
	textLineOne.setPosition(pos);
	pos.x = 78;
	pos.y = 313;
	sf::Text textLineTwo("Press  Space", font);
	textLineTwo.setCharacterSize(26);
	textLineTwo.setStyle(sf::Text::Bold);
	textLineTwo.setColor(sf::Color::Red);
	textLineTwo.setPosition(pos);
	window.draw(textLineOne);
	window.draw(textLineTwo);
	window.display();


	sf::Event menuEvent;
	while (window.pollEvent(menuEvent))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gameObjectManager.Remove("NFood");
			gameObjectManager.Remove("Pacman");
			gameObjectManager.Remove("_Blinky");
			gameObjectManager.Remove("_Pinky");
			gameObjectManager.Remove("_Inky");
			gameObjectManager.Remove("_Clyde");

			GameController::Start();
			return "menu";
		}
		if (menuEvent.type == sf::Event::Closed)
		{
			return "exit";
		}
	}
	return "";
}