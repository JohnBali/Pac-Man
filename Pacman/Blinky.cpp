#include "Blinky.h"

// Set the path
void Blinky::pathing(Map &map, sf::Vector2f PacPos)
{
	int mode = this->getMode();
	switch (mode)
	{
	case 0:							// Stopped
		this->SetSpeed(0);
		this->walk(map, PacPos);
		break;
	case 1:							// Scatter mode
		this->SetSpeed(4);
		PacPos.x = (int)this->getScatterTile().x * 16;
		PacPos.y = (int)this->getScatterTile().y * 16;
		this->walk(map, PacPos);
		break;
	case 2:							// Chase mode
		this->SetSpeed(4);
		this->walk(map, PacPos);
		break;
	case 3:							// Fritened mode
		this->SetSpeed(4);
		this->walk(map, PacPos);
		break;
	}
}

// Constructors
Blinky::Blinky()
{
	this->Load("assets/ghostRed.png");
	this->SetScale(2, 2);
	this->SetOrigin(4, 4);
	this->facing = RIGHT;
	this->SetSpeed(1);
	this->setMode(1);
	this->setScatterTile(sf::Vector2i(27, 1));
	this->_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	this->SetPosition(13, 11);
}

Blinky::~Blinky()
{
}
