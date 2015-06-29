#include "Food.h"

void Food::readMap()
{
	dots.clear();
	int rows = 0;
	int columns = 0;
	while (rows < map->ROW_COUNT)
	{
		while (columns < map->COLUMN_COUNT)
		{
			Map::Tile tile = map->getTile(rows, columns);
			if (tile == Map::Tile::TileDot)
			{
				drawDot(rows, columns);
			}
			else if (tile == Map::Tile::TileEnergizer)
			{
				drawEnergizer(rows, columns);
			}
			columns++;
		}
		columns = 0;
		rows++;
	}
}

void Food::resetBoard()
{
	int rows = 0;
	int columns = 0;
	while (rows < map->ROW_COUNT)
	{
		while (columns < map->COLUMN_COUNT)
		{
			Map::Tile tile = map->getTile(rows, columns);
			if (tile == Map::Tile::DotEaten)
			{
				map->updateTileToDot(rows, columns);
			}
			if (tile == Map::Tile::EnergizerEaten)
			{
				map->updateTileToEnergizer(rows, columns);
			}
			columns++;
		}
		columns = 0;
		rows++;
	}
}

void Food::drawDot(int rows, int columns)
{
	sf::Vector2f pos;
	pos.x = (float)(columns * 16) + 6;
	pos.y = (float)(rows * 16) + 6;
	dot.setRadius(2);
	dot.setFillColor(sf::Color(100, 250, 50));
	dot.setPosition(pos);
	dots.push_back(dot);
}

void Food::drawEnergizer(int rows, int columns)
{
	sf::Vector2f pos;
	pos.x = (float)(columns * 16) + 2;
	pos.y = (float)(rows * 16) + 2;
	dot.setRadius(6);
	dot.setFillColor(sf::Color(100, 250, 50));
	dot.setPosition(pos);
	dots.push_back(dot);
}

int* Food::getScore()
{
	return &score;
}

bool Food::getEnergizerState()
{
	return pacmanEnergized;
}

void Food::Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor)
{
	Pacman* pacman = dynamic_cast<Pacman*>(GameController::GetGameObjectManager().Get("Pacman"));
	if (pacman != NULL)
	{
		sf::Vector2f pacPos = pacman->GetPosition();
		pacmanEnergized = false;
		//check if the tile contains dot or energizer and eat it
		Map::Tile tile = map->getTile((int)pacPos.y / 16, (int)pacPos.x / 16);
		if (tile == Map::Tile::TileDot)
		{
			map->updateDotToEaten((int)pacPos.y / 16, (int)pacPos.x / 16);
			score++;
			readMap();
		}
		if (tile == Map::Tile::TileEnergizer)
		{
			pacmanEnergized = true;
			map->updateEnergizerToEaten((int)pacPos.y / 16, (int)pacPos.x / 16);
			score++;
			readMap();
		}
	}
}

void Food::Draw(sf::RenderWindow &window)
{
	for (size_t count = 0; count < dots.size(); count++)
	{
		window.draw(dots[count]);
	}
}

Food::Food()
{
	resetBoard();
	readMap();
}

Food::~Food()
{

}