#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "Pacman.h"
#include "HomeScreen.h"
#include "MainMenu.h"
#include "GameController.h"

class GameController
{
public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	static void DisplayHomeScreen();
	static void DisplayMenu();

	static sf::Event GetInput();

	enum GameState { Uninitialized, DisplayingHomeScreen, Paused, DisplayingMenu, Playing, Exiting };

	static void drawEmptyTiles(Map &map, sf::RenderWindow &window);
	static void drawGrid(sf::RenderWindow &window);

	static GameState _gameState;
	static sf::RenderWindow _window;
	static Pacman _pacman;
	static Map _map;
};