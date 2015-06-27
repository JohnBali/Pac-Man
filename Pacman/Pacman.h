#pragma once
#include "GameObject.h"
#include "Map.h"

class Pacman : public GameObject
{	
	public:
		Pacman();
		~Pacman();

		//methods
		void Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor);
		void walk(Map* map);

	private:
		Map* map;
		bool debug;

		int frame = 0;
		void Debug();
};

