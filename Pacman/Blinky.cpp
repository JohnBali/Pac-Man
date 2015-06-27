#include "Blinky.h"

// Set the path
void Blinky::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score)
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
			if (GetColumn() > 10 && GetColumn() < 17 && GetRow() < 15 && GetRow() > 11 && ghostMode != 0)
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
					this->SetSpeed(0);
					this->walk(pacPos);
					break;
				case 1:							// Scatter mode
					if (frightened)
						setGhostColor();
					this->SetSpeed(4);
					//pacPos.x = (float)getScatterTile().x * 16;			Blinky doesn't have a Scatter Mode
					//pacPos.y = (float)getScatterTile().y * 16;
					this->walk(pacPos);
					break;
				case 2:							// Chase mode
					if (frightened)
						setGhostColor();
					this->SetSpeed(4);
					this->walk(pacPos);
					break;
				case 3:							// Frightened mode
					this->SetSpeed(2);
					setGhostBlue();
					frightened = true;
					if (RowBoundary() && ColumnBoundary())
					{
						sf::Vector2i runaway = frightMode();
						pacPos.x = (float)runaway.x;
						pacPos.y = (float)runaway.y;
					}
					this->walk(pacPos);
					break;
				}
			}
			timeBetweenMoves = sf::milliseconds(25);
		}
	}
}

void Blinky::setGhostColor()
{
	Load("assets/ghostRed.png");
	SetScale(2, 2);
	SetOrigin(4, 4);

}

// Constructors
Blinky::Blinky()
{
	//turn debug on or off
	debug = false;
	frightened = false;

	setGhostColor();
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
