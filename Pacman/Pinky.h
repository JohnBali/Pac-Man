#pragma once
#include "Ghostclass.h"

class Pinky : public Ghostclass
{
private:

	void chaseMode(sf::Vector2f pacPos, Facing pacFacing);

public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor);


	// constructors
	Pinky();
	~Pinky();


};