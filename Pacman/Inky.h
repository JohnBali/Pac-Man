#pragma once
#include "Ghostclass.h"
#include "VectorMath.h"

class Inky : public Ghostclass
{
public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos);

	// constructors
	Inky();
	~Inky();


};