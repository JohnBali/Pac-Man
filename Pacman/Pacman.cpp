#include "Pacman.h"
#include <cmath>

const int Pacman::left[FRAMES] = { 6,7,8 };
const int Pacman::right[FRAMES] = { 3,4,5 };
const int Pacman::down[FRAMES] = { 0,1,2 };
const int Pacman::up[FRAMES] = { 9,10,11 };
bool Pacman::rowBoundary()
{
	return ((int)GetPosition().y % 16 == 0);
}
bool Pacman::columnBoundary()
{
	return ((int)GetPosition().x % 16 == 0);
}
int Pacman::getColumn()
{
	return GetPosition().x / 16;
}

int Pacman::getRow()
{
	return GetPosition().y / 16;
}

void Pacman::walk(Map map)
{
	sf::Vector2f pos = GetPosition();

	if (facing == RIGHT)
	{
		pos.x += 8;
		this->SetTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	}
	else if (facing == LEFT)
	{
		pos.x -= 8;
		this->SetTextureRect(sf::IntRect(left[frame] * 16, 0, 16, 16));
	}
	else if (facing == DOWN)
	{
		pos.y += 8;
		this->SetTextureRect(sf::IntRect(down[frame] * 16, 0, 16, 16));
	}
	else if (facing == UP)
	{
		pos.y -= 8;
		this->SetTextureRect(sf::IntRect(up[frame] * 16, 0, 16, 16));
	}
	SetPosition(pos.x, pos.y);
	frame = (frame + 1) % 2;
}

void Pacman::setFacing(Facing facing)
{
	this->facing = facing;
}

void Pacman::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (rowBoundary())
		{
			if (!map.isCollision(getRow(), getColumn() + 1))
			{
				setFacing(Pacman::RIGHT);
				walk(map);
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (rowBoundary())
		{
			if (!map.isCollision(getRow(), getColumn() - 1))
			{
				setFacing(Pacman::LEFT);
				walk(map);
			}
		}

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (columnBoundary())
		{
			if (!map.isCollision(getRow() + 1, getColumn()))
			{
				setFacing(Pacman::DOWN);

				walk(map);
			}
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (columnBoundary())
		{
			std::cout << "row:" << rowBoundary() << std::endl;

			if (!map.isCollision(getRow() - 1, getColumn()))
			{
				setFacing(Pacman::UP);
				walk(map);
			}
		}
	}
}

Pacman::Pacman()
{
	Load("assets/pacman.png");
	SetScale(2, 2);
	SetOrigin(4, 4);	
	GameObject::SetPosition(16, 16);
	SetTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	this->facing = RIGHT;
}

Pacman::~Pacman()
{
}
