#pragma once
#include "GameObject.h"
#include "Map.h"

class Ghostclass : public GameObject
{
public:
	// Walk
	void walk(sf::Vector2f pacPos);

	// Setters/Getters

	void setPrevTile(sf::Vector2i pos);
	sf::Vector2i getPrevTile();
	bool checkPrevTile(sf::Vector2i pos);

	void setNextTile(sf::Vector2i pos);
	sf::Vector2i getNextTile();

	void setScatterTile(sf::Vector2i pos);
	sf::Vector2i getScatterTile();

	void setMode(int mode);
	int getMode();

	// constructors
	Ghostclass();
	~Ghostclass();

protected:
	// Variables
	int mode;
	sf::Clock clock;
	sf::Vector2f previousPosition;
	sf::Vector2f nextPosition;
	sf::Vector2i previousTile01;
	sf::Vector2i previousTile02;
	sf::Vector2i previousTile03;
	sf::Vector2i nextTile;
	sf::Vector2i scatterTile;
	Map* map;
	bool debug;

	void Ghostclass::Debug(std::vector<sf::Vector2i> exits);
};
