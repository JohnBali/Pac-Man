#include "Debug.h"

Debug::Debug(GameObjectManager &gameObjectManager)
	: _gameObjectManager(gameObjectManager)
{	
}

void Debug::Draw(sf::RenderWindow &window)
{
	Map* _map = Map::instance();
	//draw tiles that show the path along which pacman and ghosts can travel
	for (int row = 0; row < _map->COLUMN_COUNT; row++)
	{
		for (int col = 0; col < _map->ROW_COUNT; col++)
		{
			Map::Tile tile = _map->getTile(col, row);
			if ((tile == Map::Tile::TileEmpty || tile == Map::Tile::TileDot) || tile == Map::Tile::TileEnergizer)
			{
				sf::RectangleShape rectangle;
				rectangle.setPosition((float)row * 16, (float)col * 16);
				rectangle.setSize(sf::Vector2f(16, 16));

				rectangle.setFillColor(sf::Color::Cyan);

				window.draw(rectangle);
			}
		}
	}

	//draw grid
	for (unsigned int y = 16; y < window.getSize().y; y += 16)
	{
		sf::Vertex line[2] = {
			sf::Vertex(sf::Vector2f(0.0f, (float)y), sf::Color(159, 159, 159, 255)),
			sf::Vertex(sf::Vector2f((float)window.getSize().x, (float)y), sf::Color(159, 159, 159, 255))
		};
		window.draw(line, 2, sf::Lines);
	}

	for (unsigned int x = 16; x < window.getSize().x; x += 16)
	{
		sf::Vertex line[2] = {
			sf::Vertex(sf::Vector2f((float)x, 0), sf::Color(159, 159, 159, 255)),
			sf::Vertex(sf::Vector2f((float)x, (float)window.getSize().y), sf::Color(159, 159, 159, 255))
		};
		window.draw(line, 2, sf::Lines);
	}
}
Map* Debug::_map;