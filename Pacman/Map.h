/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: Header of Map Class
*/

#pragma once
#include "GameObject.h"

class Map : public GameObject
{
public:
	static const int ROW_COUNT = 31;
	static const int COLUMN_COUNT = 28;
	static Map* instance();

	enum Tile {
		TileOut = -1,
		TileEmpty = 0,
		TileWall = 1,
		TileGate = 2,
		TileDot = 3,
		TileEnergizer = 4,
		TilePacman = 5,
		TileRed = 6,
		TileCyan = 7,
		TilePink = 8,
		TileOrange = 9,
		DotEaten = 10,
		EnergizerEaten = 11
	};

	void updateDotToEaten(int row, int column);
	void updateEnergizerToEaten(int row, int column);
	void updateTileToDot(int row, int column);
	void updateTileToEnergizer(int row, int column);
	Tile getTile(int row, int column);
	bool isCollision(int row, int column);
	std::vector<sf::Vector2i> getExits(int row, int column);

	~Map();

	private:
		Map();
		sf::Texture texture;
		sf::Sprite sprite;
		static int Map::DEFAULT_MAP[Map::ROW_COUNT][COLUMN_COUNT];

		static Map* _instance;
		
	
};

