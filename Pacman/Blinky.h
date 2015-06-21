#pragma once
#include "Ghostclass.h"

class Blinky : public Ghostclass
{
public:
	void Update(sf::Vector2f pacPos, sf::Time elapsed);

	// constructors
	Blinky();
	~Blinky();

private:
	bool debug;
	void Debug();

};