#pragma once
#include "Ghostclass.h"
#include "GameController.h"

class Blinky : public Ghostclass
{
private:

	sf::Vector2f chaseMode(sf::Vector2f pacPos);

public:
	void Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor);
	
	// constructors
	Blinky();
	~Blinky();


};