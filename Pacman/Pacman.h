#pragma once
#include "GameObject.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int FRAMES = 3;

class Pacman : public GameObject
{	
	public:
		Pacman();
		~Pacman();
		enum Facing
		{
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		bool rowBoundary();
		bool columnBoundary();

		int getColumn();
		int getRow();
		void walk(Map map);
		void setFacing(Facing facing);

	private:
		Facing facing;

		int frame = 0;

		static const int left[FRAMES];
		static const int right[FRAMES];
		static const int down[FRAMES];
		static const int up[FRAMES];
		sf::Texture texture;

};

