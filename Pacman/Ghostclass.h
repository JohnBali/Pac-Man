#pragma once
#include "GameObject.h"
#include "Map.h"

class Ghostclass : public GameObject
{
public:
	// Walk
	//virtual void pathing(Map &map, sf::Vector2f pacPos) = 0;
	void walk(Map* &map, sf::Vector2f pacPos);
	//void walk(Map map, sf::Vector2f pacPos);

	// Setters/Getters
	void setPrevPosition(sf::Vector2f pos);
	sf::Vector2f getPrevPosition();

	void setNextPosition(sf::Vector2f pos);
	sf::Vector2f getNextPosition();

	void setPrevTile(sf::Vector2i pos);
	sf::Vector2i getPrevTile();

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
	sf::Vector2i previousTile;
	sf::Vector2i nextTile;
	sf::Vector2i scatterTile;
	Map* map;
};
