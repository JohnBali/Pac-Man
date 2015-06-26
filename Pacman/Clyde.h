#pragma once
#include "Ghostclass.h"
#include "VectorMath.h"


class Clyde : public Ghostclass
{
public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score);

	// constructors
	Clyde();
	~Clyde();


};