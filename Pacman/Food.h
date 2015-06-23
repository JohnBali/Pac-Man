#pragma once
#include "GameObject.h"
#include "Map.h"

class Food : public GameObject
{
public:
	Food();
	~Food();

private:
	void readMap();
	void drawDot(int rows, int columns);
	void drawEnergizer(int rows, int columns);
	void Update(sf::Vector2f pacPos, sf::Time elapsed);
	void Draw(sf::RenderWindow &window);

	Map* map;
	sf::CircleShape dot;
	sf::CircleShape energizer;
	std::vector<sf::CircleShape> dots;
	std::vector<sf::CircleShape> energizers;
};