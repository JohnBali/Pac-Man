/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: This is Blinky class. This class manages the actions of Blinky ghost.
*/

#include "Blinky.h"

// Set the path
void Blinky::Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor)
{
	Pacman* pacman = dynamic_cast<Pacman*>(GameController::GetGameObjectManager().Get("Pacman"));
	if (pacman != NULL)
	{
		sf::Vector2f pacPos = pacman->GetPosition();
		timeBetweenMoves -= elapsed;
		SetColor(spriteColor.r, spriteColor.g, spriteColor.b);

		// Check ghost Win//Eaten
		if ((int)pacPos.x / 16 == GetColumn() && (int)pacPos.y / 16 == GetRow() && localMode == 3)
		{
			SetEaten(true);
			localMode = 4;
			sf::Vector2f posx = _sprite.getPosition();
			if (GetFacing() == RIGHT)
			{
				posx.x = (float)(GetColumn() + 1) * 16;
			}
			if (GetFacing() == LEFT)
			{
				posx.x = (float)(GetColumn() - 1) * 16;
			}
			if (GetFacing() == UP)
			{
				posx.y = (float)(GetRow() - 1) * 16;
			}
			if (GetFacing() == DOWN)
			{
				posx.y = (float)(GetRow() + 1) * 16;
			}
			_sprite.setPosition(posx.x, posx.y);
		}
		else if ((int)pacPos.x / 16 == GetColumn() && (int)pacPos.y / 16 == GetRow() && localMode < 3)
			SetWin();

		if (RowBoundary() && ColumnBoundary())
		{
			if (localMode != 4)
				localMode = ghostMode;
			if (getMode() != localMode)
			{
				setMode(localMode);
				modeSwitch();
			}
		}

		// Ghost sequencing just isn't working and I don't know why
		//if (score < 82)
		//	localMode = 0;

		if (!GetWin())
		{
			// Test if ghost is in ghost house
			if (ghostHouse() && localMode > 0 && localMode < 3)
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
					pacPos = stoppedMode(pacPos);
					break;
				case 1:							// Scatter mode
					setGhostImage("assets/ghostRed.png");
					frightened = false;
					pacPos = chaseMode(pacPos);	// Blinky doesn't have a scatter mode
					break;
				case 2:							// Chase mode
					pacPos = chaseMode(pacPos);
					break;
				case 3:							// Frightened mode
					pacPos = frightMode(pacPos);
					break;
				case 4:							// Eye Mode
					pacPos = eyeMode(pacPos);
					break;

				}
			}
		}
		if (timeBetweenMoves <= sf::Time::Zero)
		{
			walk(pacPos);
			timeBetweenMoves = sf::milliseconds(25);
		}
	}
}




sf::Vector2f Blinky::chaseMode(sf::Vector2f pacPos)		// Chase Mode
{
	if (frightened)
	{
		setGhostImage("assets/ghostRed.png");
		frightened = false;
	}
	this->SetSpeed(4);
	
	return pacPos;
}



// Constructors
Blinky::Blinky()
{
	//turn debug on or off
	debug = false;
	frightened = false;

	setGhostImage("assets/ghostRed.png");
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
