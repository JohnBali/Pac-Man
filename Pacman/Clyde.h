#pragma once
#include "Ghostclass.h"

class Clyde : public Ghostclass
{
public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing);

	// constructors
	Clyde();
	~Clyde();


};