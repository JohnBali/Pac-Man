/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: Header of Ghostclass Class
*/

#pragma once
#include "GameObject.h"
#include "Map.h"
#include <random>
#include "VectorMath.h"


class Ghostclass : public GameObject
{
public:
	// Walk
	void walk(sf::Vector2f pacPos);

	// Setters/Getters
	void SetWin();
	bool GetWin();

	void SetEaten(bool state);
	bool GetEaten();
	
	virtual void setMode(int mode);
	virtual int getMode();
	
	void setPrevTile(sf::Vector2i pos);
	sf::Vector2i getPrevTile();
	bool checkPrevTile(sf::Vector2i pos);
	void clearPrevTiles();

	void setNextTile(sf::Vector2i pos);
	sf::Vector2i getNextTile();

	void setScatterTile(sf::Vector2i pos);
	sf::Vector2i getScatterTile();

	void modeSwitch();
	sf::Vector2i frightExits();
	void setGhostBlue();
	void setGhostEyes();
	void setGhostImage(std::string filename);
	bool ghostHouse();
	bool ghostHouseTwo();

	bool collisionDetection(sf::Vector2f pacPos);
	
	sf::Vector2f stoppedMode(sf::Vector2f pacPos);
	sf::Vector2f Ghostclass::scatterMode(sf::Vector2f pacPos);
	sf::Vector2f frightMode(sf::Vector2f pacPos);
	sf::Vector2f eyeMode(sf::Vector2f pacPos);

	// constructors
	Ghostclass();
	~Ghostclass();

protected:
	// Variables
	
	sf::Vector2f previousPosition;
	sf::Vector2f nextPosition;
	sf::Vector2i previousTile [6];
	sf::Vector2i nextTile;
	sf::Vector2i scatterTile;
	Map* map;
	bool debug;
	bool frightened;
	int localMode;
	bool ghostWin = false;
	bool ghostEaten = false;

	void Ghostclass::Debug(std::vector<sf::Vector2i> exits);
};
