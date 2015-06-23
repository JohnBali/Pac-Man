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
		this->SetSpeed(4);
		pacPos.x = (int)this->getScatterTile().x * 16;
		pacPos.y = (int)this->getScatterTile().y * 16;
		this->walk(pacPos);
		break;
	case 2:							// Chase mode
		this->SetSpeed(4);
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
	setScatterTile(sf::Vector2i(27, 1));
	_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetPosition(208, 176);
	sf::Vector2i pos = sf::Vector2i(GetRow(), GetColumn());
	SetTile();
}

Blinky::~Blinky()
{
}
