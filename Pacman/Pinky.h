#pragma once
#include "Ghostclass.h"
#include "GameController.h"

class Pinky : public Ghostclass
{
private:

	sf::Vector2f chaseMode(sf::Vector2f pacPos, Facing pacFacing);

public:
	void Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor);


	// constructors
	Pinky();
	~Pinky();


};