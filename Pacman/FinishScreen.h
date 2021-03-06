/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: Header of FinishScreen Class
*/

#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameObjectManager.h"
#include "GameController.h"

class FinishScreen
{
public:
	std::string Show(sf::RenderWindow &window, std::string finString, GameObjectManager &gameObjectManager);

};