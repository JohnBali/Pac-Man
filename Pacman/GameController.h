#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game
{
public:
	static void Start();

private:
	static bool IsExiting();
	static void GameLoop();

	enum GameState { Uninitialized, DisplayingSplash, Paused, DisplayingMenu, Playing, Exiting};

	static GameState _gameState;
	static sf::RenderWindow _window;
};