#pragma once
#include "GameObject.h"
#include "Map.h"
#include "GameController.h"

class Food : public GameObject
{
public:
	Food();
	~Food();

	int* getScore();
	bool getEnergizerState();

private:
	void readMap();
	void resetBoard();
	void drawDot(int rows, int columns);
	void drawEnergizer(int rows, int columns);
	void Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor);
	void Draw(sf::RenderWindow &window);

	Map* map;
	sf::CircleShape dot;
	sf::CircleShape energizer;
	std::vector<sf::CircleShape> dots;
	std::vector<sf::CircleShape> energizers;
	int score = 0;
	bool pacmanEnergized = false;
};