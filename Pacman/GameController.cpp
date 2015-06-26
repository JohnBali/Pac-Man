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
	_window.draw(textLineOne);
	_window.draw(textLineTwo);
	_window.display();
	
	sf::Event menuEvent;
	while (_window.pollEvent(menuEvent))
	{
		if (menuEvent.type == sf::Event::KeyPressed)
		{
			*_score = 0;

			_gameObjectManager.Remove("NFood");
			_gameObjectManager.Remove("Pacman");
			_gameObjectManager.Remove("_Blinky");
			_gameObjectManager.Remove("_Pinky");
			_gameObjectManager.Remove("_Inky");
			_gameObjectManager.Remove("_Clyde");

			Start();
			_gameState = GameController::DisplayingMenu;
		}
		if (menuEvent.type == sf::Event::Closed)
		{
			_gameState = GameController::Exiting;
		}
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
			// Set game timer
			sf::Time ghostModes;
			if (_ghostSwitch == 0)
			{
				std::cout << "Mode: " << std::endl;
				_gameTime.restart();
				_ghostSwitch = 1;
			}

			// Game handles
			sf::Event event;
			GameObject pacman = *_gameObjectManager.Get("Pacman");
			GameObject blinky = *_gameObjectManager.Get("_Blinky");
			GameObject pinky = *_gameObjectManager.Get("_Pinky");
			GameObject inky = *_gameObjectManager.Get("_Inky");
			GameObject clyde = *_gameObjectManager.Get("_Clyde");

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
			if (*_score == 246)
			{				
				_gameState = GameController::Win;
			}

			
			if (blinky.GetWin() || pinky.GetWin() || inky.GetWin() || clyde.GetWin())
			{
				_gameState = GameController::Lose;
			}
			
			// Ghost Mode Set
			int ghostMode = 0;
			ghostModes = _gameTime.getElapsedTime();
			if (ghostModes.asSeconds() > 0 && ghostModes.asSeconds() <= 7)				//First Scatter mode
				ghostMode = 1;
			else if (ghostModes.asSeconds() > 7 && ghostModes.asSeconds() <= 27)		// First Chase mode
				ghostMode = 2;
			else if (ghostModes.asSeconds() > 27 && ghostModes.asSeconds() <= 34)		// Second Scatter mode
				ghostMode = 1;
			else if (ghostModes.asSeconds() > 34 && ghostModes.asSeconds() <= 54)		// Second Chase mode
				ghostMode = 2;
			else if (ghostModes.asSeconds() > 54 && ghostModes.asSeconds() <= 59)		// Third Scatter mode
				ghostMode = 1;
			else if (ghostModes.asSeconds() > 59 && ghostModes.asSeconds() <= 79)		// Third Chase mode
				ghostMode = 2;
			else if (ghostModes.asSeconds() > 79 && ghostModes.asSeconds() <= 84)		// Fourth Scatter mode
				ghostMode = 1;
			else if (ghostModes.asSeconds() > 84)										// Fourth and final Chase mode
				ghostMode = 2;


			// Game Updates
			sf::Vector2f pacPos = pacman.GetPosition();
			sf::Vector2f blinkyPos = blinky.GetPosition();
			GameObject::Facing facing = pacman.GetFacing();
			sf::Time elapsed = _clock.restart();
			_gameObjectManager.UpdateAll(pacPos, elapsed, facing, blinkyPos, ghostMode, *_score);


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
sf::Clock GameController::_gameTime;
int GameController::_ghostSwitch;