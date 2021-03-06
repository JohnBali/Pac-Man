/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: This is Map class. This class constructs the game map.
*/

#include "Map.h"
#include "GameObject.h"

int Map::DEFAULT_MAP[ROW_COUNT][COLUMN_COUNT] = {

//   00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },	//00
	{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },	//01
	{ 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1 },	//02
	{ 1, 4, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 4, 1 },	//03
	{ 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1 },	//04
	{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },	//05
	{ 1, 3, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 3, 1 },	//06
	{ 1, 3, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 3, 1 },	//07
	{ 1, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 1 },	//08
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//09
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//10
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//11
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//12
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//13
	{ 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 7, 7, 8, 8, 9, 9, 1, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0 },	//14
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//15
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//16
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//17
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//18
	{ 1, 1, 1, 1, 1, 1, 3, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 3, 1, 1, 1, 1, 1, 1 },	//19
	{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },	//20
	{ 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1 },	//21
	{ 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1 },	//22
	{ 1, 4, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 4, 1 },	//23
	{ 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1 },	//24
	{ 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 3, 1, 1, 1 },	//25
	{ 1, 3, 3, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 3, 3, 1 },	//26
	{ 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1 },	//27
	{ 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1 },	//28
	{ 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 1 },	//29
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }	//30
//   00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
};


Map::Tile Map::getTile(int row, int column)
{
	return Tile(DEFAULT_MAP[row][column]);
}

bool Map::isCollision(int row, int column)
{
	Map::Tile tile = getTile(row, column);
	if (tile != Map::Tile::TileWall && tile != Map::Tile::TileGate)
	{
		return false;
	}

	return true;
}

void Map::updateDotToEaten(int row, int column)
{
	Map::DEFAULT_MAP[row][column] = Map::Tile::DotEaten;
}

void Map::updateEnergizerToEaten(int row, int column)
{
	Map::DEFAULT_MAP[row][column] = Map::Tile::EnergizerEaten;
}

void Map::updateTileToDot(int row, int column)
{
	Map::DEFAULT_MAP[row][column] = Map::Tile::TileDot;
}

void Map::updateTileToEnergizer(int row, int column)
{
	Map::DEFAULT_MAP[row][column] = Map::Tile::TileEnergizer;
}

std::vector<sf::Vector2i> Map::getExits(int row, int column)
{
	// create vector to return
	std::vector<sf::Vector2i> exits;

	// find exits
	if (!(isCollision(row + 1, column)))
		exits.push_back(sf::Vector2i(row + 1, column));
	if (!(isCollision(row - 1, column)))
		exits.push_back(sf::Vector2i(row - 1, column));
	if (!(isCollision(row, column + 1)))
		exits.push_back(sf::Vector2i(row, column + 1));
	if (!(isCollision(row, column - 1)))
		exits.push_back(sf::Vector2i(row, column - 1));

	return exits;
}

Map* Map::_instance = NULL;

Map* Map::instance()
{
	if (!_instance)
	{
		_instance = new Map;
	}
	return _instance;
}

Map::Map()
{
	Load("assets/map.png");
	SetScale(2, 2);
}


Map::~Map()
{
}
