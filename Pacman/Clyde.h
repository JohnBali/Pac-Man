/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: Header of Clyde Class
*/

#pragma once
#include "Ghostclass.h"
#include "VectorMath.h"
#include "GameController.h"


class Clyde : public Ghostclass
{
private:
	sf::Vector2f chaseMode(sf::Vector2f pacPos);

public:
	void Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor);

	// constructors
	Clyde();
	~Clyde();

};