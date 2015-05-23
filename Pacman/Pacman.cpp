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

Pacman::Pacman()
{
	Load("assets/pacman.png");
	if (!texture.loadFromFile("assets/pacman.png"))
	{
		std::cout << "Error loading resource pacman.png" << std::endl;
	}

	sf::Image pacmanImage = texture.copyToImage();
	pacmanImage.createMaskFromColor(sf::Color(0, 0, 0), 0);

	if (!texture.loadFromImage(pacmanImage))
	{
		std::cout << "Error masking image resource pacman.png" << std::endl;
	}

	SetTexture(texture);
	SetScale(2, 2);
	SetOrigin(4, 4);		
	SetTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	this->facing = RIGHT;
}




Pacman::~Pacman()
{
}
