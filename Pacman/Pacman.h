/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: Header of Pacman Class
*/

#pragma once
#include "GameObject.h"
#include "Map.h"

class Pacman : public GameObject
{	
	public:
		Pacman();
		~Pacman();

		//methods
		void Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor);
		void walk(Map* map);

	private:
		Map* map;
		bool debug;

		int frame = 0;
		void Debug();
};

