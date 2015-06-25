#pragma once
#include "GameObject.h"
#include "Map.h"
#include <random>

class Ghostclass : public GameObject
{
public:
	// Walk
	void walk(sf::Vector2f pacPos);

	// Setters/Getters

	void setPrevTile(sf::Vector2i pos);
	sf::Vector2i getPrevTile();
	bool checkPrevTile(sf::Vector2i pos);
	void clearPrevTiles();

	void setNextTile(sf::Vector2i pos);
	sf::Vector2i getNextTile();

	void setScatterTile(sf::Vector2i pos);
	sf::Vector2i getScatterTile();

	void modeSwitch();
	sf::Vector2i frightMode();

	// constructors
	Ghostclass();
	~Ghostclass();

protected:
	// Variables
	
	sf::Clock clock;
	sf::Vector2f previousPosition;
	sf::Vector2f nextPosition;
	sf::Vector2i previousTile [6];
	sf::Vector2i nextTile;
	sf::Vector2i scatterTile;
	Map* map;
	bool debug;

	void Ghostclass::Debug(std::vector<sf::Vector2i> exits);
};
