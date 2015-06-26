#pragma once
#include "Ghostclass.h"

class Blinky : public Ghostclass
{
public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score);

	// constructors
	Blinky();
	~Blinky();


};