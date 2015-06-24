#include "Blinky.h"

// Set the path
void Blinky::Update(sf::Vector2f pacPos, sf::Time elapsed)
{
	int mode = this->getMode();
	switch (mode)
	{
	case 0:							// Stopped
		this->SetSpeed(0);
		this->walk(pacPos);
		break;
	case 1:							// Scatter mode
		this->SetSpeed(8);
		pacPos.x = (int)this->getScatterTile().x * 16;
		pacPos.y = (int)this->getScatterTile().y * 16;
		this->walk(pacPos);
		break;
	case 2:							// Chase mode
		this->SetSpeed(2);
		this->walk(pacPos);
		break;
	case 3:							// Fritened mode
		this->SetSpeed(4);
		this->walk(pacPos);
		break;
	}

}

// Constructors
Blinky::Blinky()
{
	//turn debug on or off
	debug = false;

	Load("assets/ghostRed.png");
	SetScale(2, 2);
	SetOrigin(4, 4);
	SetFacing(RIGHT);
	SetSpeed(1);
	setMode(1);
	setScatterTile(sf::Vector2i(24, 0));
	_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetPosition(16, 16);
	SetTile();
	setPrevTile(sf::Vector2i(0, 1));
}

Blinky::~Blinky()
{
}
