#include "Inky.h"

// Set the path
void Inky::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		// Variables
		int localMode = ghostMode;
		int localScore = score;

		//if (localScore < 30)
		//	localMode = 0;

		if (getMode() != ghostMode)
		{
			setMode(ghostMode);
			modeSwitch();
		}


		// Check ghost Win
		if ((int)pacPos.x / 16 == GetColumn() && (int)pacPos.y / 16 == GetRow())
			SetWin();

		if (!GetWin())
		{
			// Test if ghost is in ghost house and exit if it is
			if (ghostHouse() && localMode != 0)
			{
				clearPrevTiles();
				pacPos = (sf::Vector2f(216, 80));
				this->walk(pacPos);
			}
			else
			{
				// Mode and path switch
				switch (localMode)
				{
				case 0:							// Stopped
					break;
				case 1:							// Scatter mode
					break;
				case 2:							// Chase mode
					break;
				case 3:							/// Frightened mode
					break;
				case 4:
					break;
				}
			}
			timeBetweenMoves = sf::milliseconds(25);
		}
	}
}


void Inky::chaseMode(sf::Vector2f pacPos, sf::Vector2f blinkyPos)		// Chase Mode
{
	sf::Vector2f temp = pacPos;

	if (frightened)
	{
		setGhostImage("assets/ghostCyan.png");
		frightened = false;
	}
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

}


// Constructors
Inky::Inky()
{
	//turn debug on or off
	debug = false;
	frightened = false;

	setGhostImage("assets/ghostCyan.png");
	SetFacing(RIGHT);

	setMode(0);
	setScatterTile(sf::Vector2i(22, 30));
	_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetPosition(184, 224);
	SetTile();
	setPrevTile(sf::Vector2i(0, 1));
}

Inky::~Inky()
{
}
