#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML\System.hpp"

#include "Map.h"
#include "Pacman.h"
#include "HomeScreen.h"
#include "MainMenu.h"
#include "GameController.h"
#include "GameObjectManager.h"
#include <string>
#include "Food.h"
#include "Debug.h"

// Add ghost includes
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

class GameController
{
public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void DisplayHomeScreen();
	static void DisplayMenu();
	static void DisplayWinScreen();
	static void DisplayLoseScreen();
	static void DisplayFinishScreen(std::string finString);

	static sf::Event GetInput();

	enum GameState { Uninitialized, DisplayingHomeScreen, Paused, DisplayingMenu, Playing, Win, Lose, Exiting };

	static int* _score;
	static GameState _gameState;
	static sf::RenderWindow _window;
	static Map* _map;
	static GameObjectManager _gameObjectManager;
	static bool _debug;
	static sf::Clock _clock;
	static sf::Clock _gameTime;
	static int _ghostSwitch;
};