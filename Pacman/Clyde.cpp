#include "Clyde.h"

// Set the path
void Clyde::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score, sf::Color spriteColor)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		// Variables
		int localMode = ghostMode;
		SetColor(spriteColor.r, spriteColor.g, spriteColor.b);

		//if (score < 82)
		//	localMode = 0;

		if (getMode() != localMode)
		{
			setMode(localMode);
			modeSwitch();
		}

		// Check ghost Win
		if ((int)pacPos.x / 16 == GetColumn() && (int)pacPos.y / 16 == GetRow())
			SetWin();

		if (!GetWin())
		{
			// Test if ghost is in ghost house
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
					stoppedMode(pacPos);
					break;
				case 1:							// Scatter mode
					scatterMode(pacPos);
					break;
				case 2:							// Chase mode
					chaseMode(pacPos);
					break;
				case 3:							// Frightened mode
					frightMode(pacPos);
					break;
				case 4:							// Eye Mode
					eyeMode(pacPos);
					break;

				}
			}
			timeBetweenMoves = sf::milliseconds(25);
		}
	}
}




void Clyde::scatterMode(sf::Vector2f pacPos)		// Scatter Mode
{
	if (frightened)
	{
		setGhostColor("assets/ghostOrange.png");
		frightened = false;
	}
	this->SetSpeed(4);
	pacPos.x = (float)this->getScatterTile().x * 16;
	pacPos.y = (float)this->getScatterTile().y * 16;
	this->walk(pacPos);

}

void Clyde::chaseMode(sf::Vector2f pacPos)			// Chase Mode
{
	float distance = 0.0;
	sf::Vector2f ghostPos = GetPosition();

	if (frightened)
	{
		setGhostColor("assets/ghostOrange.png");
		frightened = false;
	}
	this->SetSpeed(4);
	distance = vm::magnitude(sf::Vector2f(ghostPos.x - pacPos.x, ghostPos.y - pacPos.y));
	if (distance < 128)
	{
		pacPos.x = (float)this->getScatterTile().x * 16;
		pacPos.y = (float)this->getScatterTile().y * 16;
	}
	walk(pacPos);

}



// Constructors
Clyde::Clyde()
{
	//turn debug on or off
	debug = false;
	frightened = false;

	setGhostColor("assets/ghostOrange.png");
	SetFacing(LEFT);

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
