#pragma once
#include "GameObject.h"
#include "Map.h"

class Pacman : public GameObject
{	
	public:
		Pacman();
		~Pacman();

		//methods
		void Update(sf::Vector2f pacPos, sf::Time elapsed);
		void walk(Map map);

	private:
		Map map;
		bool debug;
		sf::Time timeBetweenMoves;

		int frame = 0;
		void Debug();
};

