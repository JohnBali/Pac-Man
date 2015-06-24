#include "Pinky.h"

// Set the path
void Pinky::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		// Variables
		int mode = this->getMode();

		// Mode and path switch
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
			switch (facing)
			{
			case GameObject::LEFT:
				pacPos.x -= 64;
				break;
			case GameObject::RIGHT:
				pacPos.x += 64;
				break;
			case GameObject::UP:
				pacPos.y -= 64;
				break;
			case GameObject::DOWN:
				pacPos.y += 64;
				break;
			}
			this->walk(pacPos);
			break;
		case 3:							// Fritened mode
			this->SetSpeed(4);
			this->walk(pacPos);
			break;
		}
		timeBetweenMoves = sf::milliseconds(25);
	}
}

// Constructors
Pinky::Pinky()
{
	//turn debug on or off
	debug = true;

	Load("assets/ghostPink.png");
	SetScale(2, 2);
	SetOrigin(4, 4);
	SetFacing(RIGHT);

	setMode(0);
	setScatterTile(sf::Vector2i(5, 0));
	_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetPosition(216, 224);
	SetTile();
	setPrevTile(sf::Vector2i(0, 1));
}

Pinky::~Pinky()
{
}
