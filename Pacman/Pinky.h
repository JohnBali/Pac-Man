#pragma once
#include "Ghostclass.h"

class Pinky : public Ghostclass
{
public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos);

	// constructors
	Pinky();
	~Pinky();


};