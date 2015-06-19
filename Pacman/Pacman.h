#pragma once
#include "GameObject.h"
#include "Map.h"

class Pacman : public GameObject
{	
	public:
		Pacman();
		~Pacman();

		//methods
		void Update(sf::Vector2f pacPos);
		void walk(Map map);

	private:
		Map map;
		bool debug;

		int frame = 0;
		void Debug();
};

