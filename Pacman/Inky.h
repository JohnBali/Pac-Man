#pragma once
#include "Ghostclass.h"
#include "VectorMath.h"

class Inky : public Ghostclass
{
private:

	void scatterMode(sf::Vector2f pacPos);
	void chaseMode(sf::Vector2f pacPos, sf::Vector2f blinkyPos);

public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor);

	// constructors
	Inky();
	~Inky();


};