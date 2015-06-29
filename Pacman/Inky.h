/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: Header of Inky Class
*/

#pragma once
#include "Ghostclass.h"
#include "VectorMath.h"
#include "GameController.h"

class Inky : public Ghostclass
{
private:
	sf::Vector2f chaseMode(sf::Vector2f pacPos, sf::Vector2f blinkyPos);

public:
	void Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor);

	// constructors
	Inky();
	~Inky();


};