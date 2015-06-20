#include "GameController.h"
#include "Pacman.h"
#include "Map.h"
#include "Debug.h"
#include "HomeScreen.h"
#include "MainMenu.h"
#include "Blinky.h"

void GameController::Start(void)
{
	//create objects
	Pacman *pacman = new Pacman();	
	Blinky *blinky = new Blinky();
	//Map *map = new Map();
	Map::instance();

	if (_debug)
	{
		Debug *debug = new Debug(_gameObjectManager);
		_gameObjectManager.Add("Outline", debug);
	}

	//add to game object manager
	_gameObjectManager.Add("Pacman", pacman);
	_gameObjectManager.Add("Blinky", blinky);
	_gameObjectManager.Add("Map", _map);

	if (_gameState != Uninitialized)
		return;

	_window.create(sf::VideoMode(448, 496), "Pacman");
	_window.setFramerateLimit(60);

	_gameState = GameController::DisplayingHomeScreen;

	while (!IsExiting())
	{
		GameLoop();
	}
	_window.close();
}

bool GameController::IsExiting()
{
	if (_gameState == GameController::Exiting)
		return true;
	else
		return false;
}

void GameController::DisplayHomeScreen()
{
	HomeScreen homeScreen;
	homeScreen.Show(_window);
	_gameState = GameController::DisplayingMenu;
}

void GameController::DisplayMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_window);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = GameController::Exiting;
		break;
	case MainMenu::Play:
		_gameState = GameController::Playing;
		break;
	}
}

sf::Event GameController::GetInput()
{
	sf::Event event;
	_window.pollEvent(event);
	return event;
}

void GameController::GameLoop()
{
	bool drawGridCells = true;
	bool drawEmptyPath = true;

	switch (_gameState)
	{
		case GameController::DisplayingHomeScreen:
		{
			DisplayHomeScreen();
			break;
		}
		case GameController::DisplayingMenu:
		{
			DisplayMenu();
			break;
		}
		case GameController::Playing:
		{
			sf::Event event;
			while (_window.pollEvent(event))
			{
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed)
				{
					_window.close();
				}
			}
			GameObject pacman = *_gameObjectManager.Get("Pacman");
			sf::Vector2f pacPos = pacman.GetPosition();
			sf::Time elapsed = _clock.restart();
			_gameObjectManager.UpdateAll(pacPos, elapsed);

			_window.clear();		
			_gameObjectManager.DrawAll(_window);

			if (_debug)
			{
				GameObject pacman = *_gameObjectManager.Get("Pacman");
				sf::RectangleShape boundingBox;
				boundingBox.setSize(sf::Vector2f(32, 32));
				boundingBox.setOrigin(8, 8);
				boundingBox.setPosition(pacman.GetPosition());
				boundingBox.setFillColor(sf::Color(0, 0, 0, 0));
				boundingBox.setOutlineColor(sf::Color::Red);
				boundingBox.setOutlineThickness(3);

				_window.draw(boundingBox);
			}
			
			_window.display();
			break;
		}
	}	
}

GameController::GameState GameController::_gameState = Uninitialized;
sf::RenderWindow GameController::_window;
Map* GameController::_map = Map::instance();
GameObjectManager GameController::_gameObjectManager;
bool GameController::_debug = false;
sf::Clock GameController::_clock;