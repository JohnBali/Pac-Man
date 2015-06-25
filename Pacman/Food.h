#pragma once
#include "GameObject.h"
#include "Map.h"

class Food : public GameObject
{
public:
	Food();
	~Food();

	int* getScore();

private:
	void readMap();
	void resetBoard();
	void drawDot(int rows, int columns);
	void drawEnergizer(int rows, int columns);
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos);
	void Draw(sf::RenderWindow &window);

	Map* map;
	sf::CircleShape dot;
	sf::CircleShape energizer;
	std::vector<sf::CircleShape> dots;
	std::vector<sf::CircleShape> energizers;
	int score = 0;
};