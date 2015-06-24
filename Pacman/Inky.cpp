#include "Inky.h"

// Set the path
void Inky::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		// Variables
		int mode = this->getMode();
		sf::Vector2f temp = pacPos;

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
				temp.x -= 32;
				break;
			case GameObject::RIGHT:
				temp.x += 32;
				break;
			case GameObject::UP:
				temp.y -= 32;
				break;
			case GameObject::DOWN:
				temp.y += 32;
				break;
			}
			temp.x = (temp.x - blinkyPos.x) * 2;
			temp.y = (temp.y - blinkyPos.y) * 2;
			pacPos.x += temp.x;
			pacPos.y += temp.y;
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
Inky::Inky()
{
	//turn debug on or off
	debug = false;

	Load("assets/ghostCyan.png");
	SetScale(2, 2);
	SetOrigin(4, 4);
	SetFacing(RIGHT);

	setMode(2);
	setScatterTile(sf::Vector2i(22, 30));
	_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetPosition(16, 16);	//(184, 224);
	SetTile();
	setPrevTile(sf::Vector2i(0, 1));
}

Inky::~Inky()
{
}
