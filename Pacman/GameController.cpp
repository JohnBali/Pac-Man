#include "GameController.h"
#include "Pacman.h"
#include "Map.h"
#include "HomeScreen.h"
#include "MainMenu.h"

void GameController::Start(void)
{
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

void GameController::drawEmptyTiles(Map &map, sf::RenderWindow &window)
{
	for (int row = 0; row < map.COLUMN_COUNT; row++)
	{
		for (int col = 0; col < map.ROW_COUNT; col++)
		{
			Map::Tile tile = map.getTile(col, row);
			if ((tile == Map::Tile::TileEmpty || tile == Map::Tile::TileDot) || tile == Map::Tile::TileEnergizer)
			{
				sf::RectangleShape rectangle;
				rectangle.setPosition(row * 16, col * 16);
				rectangle.setSize(sf::Vector2f(16, 16));

				rectangle.setFillColor(sf::Color::Cyan);

				window.draw(rectangle);
			}
		}
	}
}

void GameController::drawGrid(sf::RenderWindow &window)
{
	for (int y = 16; y < window.getSize().y; y += 16)
	{
		sf::Vertex line[2] = {
			sf::Vertex(sf::Vector2f(0.0f, y), sf::Color(159, 159, 159, 255)),
			sf::Vertex(sf::Vector2f(window.getSize().x, y), sf::Color(159, 159, 159, 255))
		};
		window.draw(line, 2, sf::Lines);
	}

	for (int x = 16; x < window.getSize().x; x += 16)
	{
		sf::Vertex line[2] = {
			sf::Vertex(sf::Vector2f(x, 0), sf::Color(159, 159, 159, 255)),
			sf::Vertex(sf::Vector2f(x, window.getSize().y), sf::Color(159, 159, 159, 255))
		};
		window.draw(line, 2, sf::Lines);
	}
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
	bool debug = true;
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
				_pacman.Update();
			}

			_window.clear();

			if (debug)
			{
				std::cout << "actual position: (" << _pacman.GetPosition().x << ", " << _pacman.GetPosition().y << ")" << std::endl;
				std::cout << "grid position: (" << _pacman.getRow() << "," << _pacman.getColumn() << ")" << std::endl;

				std::cout << "map tile: " << _map.getTile(_pacman.getRow(), _pacman.getColumn()) << std::endl;
			}

			_map.Draw(_window);

			if (drawGridCells)
			{
				if (drawEmptyPath)
				{
					drawEmptyTiles(_map, _window);
				}

				drawGrid(_window);
			}

			_pacman.Draw(_window);
			if (debug)
			{
				sf::RectangleShape boundingBox;
				boundingBox.setSize(sf::Vector2f(32, 32));
				boundingBox.setOrigin(8, 8);
				boundingBox.setPosition(_pacman.GetPosition());
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
Pacman GameController::_pacman;
Map GameController::_map;