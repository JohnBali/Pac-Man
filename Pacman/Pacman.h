#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"

const int FRAMES = 3;

class Pacman
{
	public:
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
		sf::Sprite getSprite();
		void setFacing(Facing facing);
		void setPosition(int row, int column);
		Pacman();
		~Pacman();

	private:
		Facing facing;

		int frame;

		static const int left[FRAMES];
		static const int right[FRAMES];
		static const int down[FRAMES];
		static const int up[FRAMES];
		sf::Sprite sprite;
		sf::Texture texture;

};

