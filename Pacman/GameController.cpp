#include "GameController.h"

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
	Score *score = new Score();

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
	_gameObjectManager.Add("Score", score);

	if (_gameState != Uninitialized)
		return;

	_window.create(sf::VideoMode(448, 534), "Pacman");
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

void GameController::DisplayFinishScreen(std::string finString)
{
	FinishScreen finishScreen;
	std::string result = finishScreen.Show(_window, finString, _gameObjectManager);
	if (result == "menu")
	{
		_gameState = GameController::DisplayingMenu;
	}
	else if (result == "exit")
	{
		_gameState = GameController::Exiting;
	}
}

void GameController::DisplayLoseScreen()
{
	DisplayFinishScreen("You Lost");
}

void GameController::DisplayWinScreen()
{
	DisplayFinishScreen("You Win");
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

const GameObjectManager& GameController::GetGameObjectManager()
{
	return GameController::_gameObjectManager;
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
			_ghostSwitch = 0;
			DisplayMenu();
			break;
		}
		case GameController::Win:
		{
			DisplayWinScreen();
			break;
		}
		case GameController::Lose:
		{
			DisplayLoseScreen();
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
					_gameState = GameController::Exiting;
				}
			}
			//check if all dots are eaten and game is won
			Food* food = dynamic_cast<Food*>(_gameObjectManager.Get("NFood"));
			if (food != NULL)
			{
				if (*food->getScore() == 246)
				{
					_gameState = GameController::Win;
				}
			}			

			// Object handles																These are temporary, only exist in this method
			Ghostclass* blinky = dynamic_cast<Ghostclass*>(_gameObjectManager.Get("_Blinky"));
			Ghostclass* pinky = dynamic_cast<Ghostclass*>(_gameObjectManager.Get("_Pinky"));
			Ghostclass* inky = dynamic_cast<Ghostclass*>(_gameObjectManager.Get("_Inky"));
			Ghostclass* clyde = dynamic_cast<Ghostclass*>(_gameObjectManager.Get("_Clyde"));
			
			if (blinky->GetWin() || pinky->GetWin() || inky->GetWin() || clyde->GetWin())
			{
				_gameState = GameController::Lose;
			}			
			
			// Game Updates
			UpdateGhostModes(food);
			sf::Time elapsed = _clock.restart();
			_gameObjectManager.UpdateAll(elapsed, ghostMode, spriteColor);

			_window.clear();		
			_gameObjectManager.DrawAll(_window);

			if (_debug)
			{
				sf::RectangleShape boundingBox;
				boundingBox.setSize(sf::Vector2f(32, 32));
				boundingBox.setOrigin(8, 8);
				boundingBox.setPosition(blinky->GetPosition());
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

void GameController::UpdateGhostModes(Food* food)
{
	// Set game timer
	sf::Time ghostModes;
	sf::Time frightModes;
	if (_ghostSwitch == 0)
	{
		std::cout << "Mode: " << std::endl;
		_gameTime.restart();
		_ghostSwitch = 1;
	}
	// Ghost Mode Set
	ghostModes = _gameTime.getElapsedTime();

	if (food->getEnergizerState())															// Check if Pacman has eaten an Energiser
	{
		//update mode to frightened
		ghostMode = 3;
		ghostModeTimer += 4;
		frightModes = _frightTime.restart();
		//*_pacmanEnergized = false;
	}
	else if (ghostMode == 3)																// Flash the frightened ghosts
	{
		frightModes = _frightTime.getElapsedTime();
		if (frightModes.asSeconds() > 2.5 && frightModes.asSeconds() < 3)
			spriteColor = (sf::Color(0, 64, 64));
		else if (frightModes.asSeconds() > 3 && frightModes.asSeconds() < 3.5)
			spriteColor = (sf::Color(255, 255, 255));
		else if (frightModes.asSeconds() > 3.5 && frightModes.asSeconds() < 4)
			spriteColor = (sf::Color(0, 64, 64));
		else if (frightModes.asSeconds() > 4)
		{
			ghostMode = 1;
			spriteColor = (sf::Color(255, 255, 255));
		}
	}
	else
	{																												// Set standard ghost modes
		if (ghostModes.asSeconds() > 0 && ghostModes.asSeconds() <= 4 + ghostModeTimer)								//First Scatter mode
			ghostMode = 1;
		else if (ghostModes.asSeconds() > 4 + ghostModeTimer && ghostModes.asSeconds() <= 24 + ghostModeTimer)		// First Chase mode
			ghostMode = 2;
		else if (ghostModes.asSeconds() > 24 + ghostModeTimer && ghostModes.asSeconds() <= 28 + ghostModeTimer)		// Second Scatter mode
			ghostMode = 1;
		else if (ghostModes.asSeconds() > 28 + ghostModeTimer && ghostModes.asSeconds() <= 48 + ghostModeTimer)		// Second Chase mode
			ghostMode = 2;
		else if (ghostModes.asSeconds() > 48 + ghostModeTimer && ghostModes.asSeconds() <= 52 + ghostModeTimer)		// Third Scatter mode
			ghostMode = 1;
		else if (ghostModes.asSeconds() > 52 + ghostModeTimer && ghostModes.asSeconds() <= 72 + ghostModeTimer)		// Third Chase mode
			ghostMode = 2;
		else if (ghostModes.asSeconds() > 72 + ghostModeTimer && ghostModes.asSeconds() <= 76 + ghostModeTimer)		// Fourth Scatter mode
			ghostMode = 1;
		else if (ghostModes.asSeconds() > 76 + ghostModeTimer)														// Fourth and final Chase mode
			ghostMode = 2;
	}
}

GameController::GameState GameController::_gameState = Uninitialized;
sf::RenderWindow GameController::_window;
Map* GameController::_map = Map::instance();
GameObjectManager GameController::_gameObjectManager;
bool GameController::_debug = false;
sf::Clock GameController::_clock;
sf::Clock GameController::_gameTime;
sf::Clock GameController::_frightTime;
sf::Color GameController::spriteColor = (sf::Color(255, 255, 255));
int GameController::_ghostSwitch;
int GameController::ghostMode = 0;
int GameController::ghostModeTimer = 0;