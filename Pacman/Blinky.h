#pragma once
#include "Ghostclass.h"

class Blinky : public Ghostclass
{
public:
	void pathing(sf::Vector2f PacPos);

	// constructors
	Blinky();
	~Blinky();
};