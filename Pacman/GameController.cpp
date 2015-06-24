#include "GameController.h"
#include "Pacman.h"
#include "Map.h"
#include "Debug.h"
#include "HomeScreen.h"
#include "MainMenu.h"
#include "Food.h"

// Add ghost includes
#include "Blinky.h"
#include "Pinky.h"
#include "Inky.h"
#include "Clyde.h"

void GameController::Start(void)
{
	//create objects
	Pacman *pacman = new Pacman();	
	// Add ghosts
	Blinky *blinky = new Blinky();
	Pinky *pinky = new Pinky();
	Inky *inky = new Inky();
	Clyde *clyde = new Clyde();

	Food *food = new Food();
	_score = food->getScore();

	//create a pointer to the score in the food class which is used to work out when the level is complete
	_score = food->getScore();

	if (_debug)
	{
		Debug *debug = new Debug(_gameObjectManager);
		_gameObjectManager.Add("Outline", debug);
	}

	//add to game object manager. Layers displayed in alphabetical order
	_gameObjectManager.Add("Map", _map);
	_gameObjectManager.Add("NFood", food);
	_gameObjectManager.Add("Pacman", pacman);
	// Add ghosts
	_gameObjectManager.Add("_Blinky", blinky);
	_gameObjectManager.Add("_Pinky", pinky);
	_gameObjectManager.Add("_Inky", inky);
	_gameObjectManager.Add("_Clyde", clyde);

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
		case GameController::Win:
		{
			std::cout << "WIN" << std::endl;
			break;
		}
		case GameController::Lose:
		{
			std::cout << "LOSE" << std::endl;
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
			//check if all dots are eaten and game is won
			if (*_score == 246)
			{
				_gameState = GameController::Win;
			}

			GameObject pacman = *_gameObjectManager.Get("Pacman");
			GameObject blinky = *_gameObjectManager.Get("_Blinky");
			
			//check if all dots are eaten and game is won
			if (*_score == 246)
			{
				_gameState = GameController::Win;
			}

			sf::Vector2f pacPos = pacman.GetPosition();
			sf::Vector2f blinkyPos = blinky.GetPosition();
			GameObject::Facing facing = pacman.GetFacing();
			sf::Time elapsed = _clock.restart();
			_gameObjectManager.UpdateAll(pacPos, elapsed, facing, blinkyPos);

			_window.clear();		
			_gameObjectManager.DrawAll(_window);

			if (_debug)
			{
				sf::RectangleShape boundingBox;
				boundingBox.setSize(sf::Vector2f(32, 32));
				boundingBox.setOrigin(8, 8);
				boundingBox.setPosition(blinky.GetPosition());
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
int* GameController::_score;