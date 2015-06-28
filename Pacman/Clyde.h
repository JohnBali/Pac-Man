#pragma once
#include "Ghostclass.h"
#include "VectorMath.h"


class Clyde : public Ghostclass
{
private:
	sf::Vector2f chaseMode(sf::Vector2f pacPos);

public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor);

	// constructors
	Clyde();
	~Clyde();

};