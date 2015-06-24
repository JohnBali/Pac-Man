#include "Clyde.h"

// Set the path
void Clyde::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		// Variables
		int mode = this->getMode();
		sf::Vector2f ghostPos = GetPosition();
		float distance = 0.0;

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
			distance = vm::magnitude(sf::Vector2f(ghostPos.x - pacPos.x, ghostPos.y - pacPos.y));
			if (distance < 128)
			{
				pacPos.x = (int)this->getScatterTile().x * 16;
				pacPos.y = (int)this->getScatterTile().y * 16;
			}
			walk(pacPos);
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
Clyde::Clyde()
{
	//turn debug on or off
	debug = false;

	Load("assets/ghostOrange.png");
	SetScale(2, 2);
	SetOrigin(4, 4);
	SetFacing(RIGHT);

	setMode(0);
	setScatterTile(sf::Vector2i(5, 30));
	_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetPosition(248, 224);
	SetTile();
	setPrevTile(sf::Vector2i(0, 1));
}

Clyde::~Clyde()
{
}