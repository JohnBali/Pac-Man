#include "GameController.h"
#include "Pacman.h"
#include "Map.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_window.create(sf::VideoMode(448, 496), "Pacman");
	_window.setFramerateLimit(60);

	while (!IsExiting())
	{
		GameLoop();
	}
	_window.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void drawEmptyTiles(Map &map, sf::RenderWindow &window)
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

void drawGrid(sf::RenderWindow &window)
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

void Game::GameLoop()
{
	bool debug = true;
	bool drawGridCells = true;
	bool drawEmptyPath = true;

	Pacman pacman;
	Map map;

	pacman.setPosition(1, 1);

	sf::Event event;
	while (_window.pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
		{
			_window.close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (pacman.rowBoundary())
			{
				if (!map.isCollision(pacman.getRow(), pacman.getColumn() + 1))
				{
					pacman.setFacing(Pacman::RIGHT);
					pacman.walk(map);
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (pacman.rowBoundary())
			{
				if (!map.isCollision(pacman.getRow(), pacman.getColumn() - 1))
				{
					pacman.setFacing(Pacman::LEFT);
					pacman.walk(map);
				}
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (pacman.columnBoundary())
			{
				if (!map.isCollision(pacman.getRow() + 1, pacman.getColumn()))
				{
					pacman.setFacing(Pacman::DOWN);

					pacman.walk(map);
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (pacman.columnBoundary())
			{
				std::cout << "row:" << pacman.rowBoundary() << std::endl;

				if (!map.isCollision(pacman.getRow() - 1, pacman.getColumn()))
				{
					pacman.setFacing(Pacman::UP);
					pacman.walk(map);
				}
			}
		}
	}

	_window.clear();

	if (debug)
	{
		std::cout << "actual position: (" << pacman.getSprite().getPosition().x << ", " << pacman.getSprite().getPosition().y << ")" << std::endl;
		std::cout << "grid position: (" << pacman.getRow() << "," << pacman.getColumn() << ")" << std::endl;

		std::cout << "map tile: " << map.getTile(pacman.getRow(), pacman.getColumn()) << std::endl;
	}

	_window.draw(map.getSprite());

	if (drawGridCells)
	{
		if (drawEmptyPath)
		{
			drawEmptyTiles(map, _window);
		}

		drawGrid(_window);
	}

	_window.draw(pacman.getSprite());
	if (debug)
	{
		sf::RectangleShape boundingBox;
		boundingBox.setSize(sf::Vector2f(32, 32));
		boundingBox.setOrigin(8, 8);
		boundingBox.setPosition(pacman.getSprite().getPosition());
		boundingBox.setFillColor(sf::Color(0, 0, 0, 0));
		boundingBox.setOutlineColor(sf::Color::Red);
		boundingBox.setOutlineThickness(3);

		_window.draw(boundingBox);
	}
	_window.display();
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_window;