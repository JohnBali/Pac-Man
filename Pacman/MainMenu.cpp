#include "MainMenu.h" 
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	sf::Texture image;
	image.loadFromFile("assets/mainMenu.png");
	sf::Sprite sprite(image);
	MenuItem playButton;
	playButton.rect.top = 92;
	playButton.rect.height = 155;
	playButton.rect.left = 0;
	playButton.rect.width = 448;
	playButton.action = Play;
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.width = 448;
	exitButton.rect.top = 247;
	exitButton.rect.height = 119;
	exitButton.action = Exit;
	
	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);
	
	window.draw(sprite);
	window.display();
	
	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it; 
	
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.top + menuItemRect.height > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width > x)
		{
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent; 
	
	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}