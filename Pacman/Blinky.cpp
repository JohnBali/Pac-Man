#include "Blinky.h"

// Set the path
void Blinky::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		// Variables
		if (getMode() != ghostMode)
		{
			setMode(ghostMode);
			modeSwitch();
		}

		// Check ghost Win
		if ((int)pacPos.x / 16 == GetColumn() && (int)pacPos.y / 16 == GetRow())
			SetWin();

		// Mode and path switch
		if (!GetWin())
		{
			// Test if ghost is in ghost house
			if (ghostHouse() && ghostMode != 0)
			{
				clearPrevTiles();
				pacPos = (sf::Vector2f(216, 80));
				this->walk(pacPos);
			}
			else
			{
				switch (ghostMode)
				{
				case 0:							// Stopped
					break;
				case 1:							// Scatter mode
					break;
				case 2:							// Chase mode
					break;
				case 3:							// Frightened mode
					break;
				case 4:
					break;
				}
			}
			timeBetweenMoves = sf::milliseconds(25);
		}
	}
}


void Blinky::scatterMode(sf::Vector2f pacPos)	//Blinky doesn't have a Scatter Mode
{
	if (frightened)
	{
		setGhostColor("assets/ghostRed.png");
		frightened = false;
	}
	this->SetSpeed(4);
	this->walk(pacPos);
}

void Blinky::chaseMode(sf::Vector2f pacPos)		// Chase Mode
{
	if (frightened)
	{
		setGhostColor("assets/ghostRed.png");
		frightened = false;
	}
	this->SetSpeed(4);
	this->walk(pacPos);
}



// Constructors
Blinky::Blinky()
{
	//turn debug on or off
	debug = false;
	frightened = false;

	setGhostColor("assets/ghostRed.png");
	SetFacing(RIGHT);
	
	setMode(0);
	setScatterTile(sf::Vector2i(22, 0));
	_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetPosition(216, 176);
	SetTile();
	setPrevTile(sf::Vector2i(0, 1));
}

Blinky::~Blinky()
{
}
