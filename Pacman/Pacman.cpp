#include "Pacman.h"
#include <cmath>

const int Pacman::left[FRAMES] = { 6,7,8 };
const int Pacman::right[FRAMES] = { 3,4,5 };
const int Pacman::down[FRAMES] = { 0,1,2 };
const int Pacman::up[FRAMES] = { 9,10,11 };
bool Pacman::rowBoundary()
{
	return ((int)sprite.getPosition().y % 16 == 0);
}
bool Pacman::columnBoundary()
{
	return ((int)sprite.getPosition().x % 16 == 0);
}
int Pacman::getColumn()
{
	return sprite.getPosition().x / 16;
}

int Pacman::getRow()
{
	return sprite.getPosition().y / 16;
}

void Pacman::walk(Map map)
{
	sf::Vector2f pos = sprite.getPosition();

	if (facing == RIGHT)
	{
		pos.x += 8;
		this->sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	}
	else if (facing == LEFT)
	{
		pos.x -= 8;
		this->sprite.setTextureRect(sf::IntRect(left[frame] * 16, 0, 16, 16));
	}
	else if (facing == DOWN)
	{
		pos.y += 8;
		this->sprite.setTextureRect(sf::IntRect(down[frame] * 16, 0, 16, 16));
	}
	else if (facing == UP)
	{
		pos.y -= 8;
		this->sprite.setTextureRect(sf::IntRect(up[frame] * 16, 0, 16, 16));
	}
	sprite.setPosition(pos);
	frame = (frame + 1) % 2;
}

sf::Sprite Pacman::getSprite()
{
	return sprite;
}

void Pacman::setFacing(Facing facing)
{
	this->facing = facing;
}

void Pacman::setPosition(int row, int column)
{
	sprite.setPosition(row * 16, column * 16);
}

Pacman::Pacman()
{
	
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

	this->sprite.setTexture(texture);
	this->sprite.setScale(2, 2);
	this->sprite.setOrigin(4,4);
	
	this->facing = RIGHT;

	this->sprite.setTextureRect(sf::IntRect(right[frame]*16, 0,16,16));
}




Pacman::~Pacman()
{
}
