#pragma once
#include "Ghostclass.h"

class Blinky : public Ghostclass
{
private:

	void chaseMode(sf::Vector2f pacPos);

public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor);
	
	// constructors
	Blinky();
	~Blinky();


};