#pragma once
#include "Ghostclass.h"

class Inky : public Ghostclass
{
public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing);

	// constructors
	Inky();
	~Inky();


};