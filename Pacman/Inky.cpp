/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: This is Inky class. This class manages the actions of Inky ghost.
*/

#include "Inky.h"

// Set the path
void Inky::Update(sf::Time elapsed, int ghostMode, sf::Color spriteColor)
{
	Blinky* blinky = dynamic_cast<Blinky*>(GameController::GetGameObjectManager().Get("_Blinky"));
	sf::Vector2f blinkyPos = blinky->GetPosition();

	Pacman* pacman = dynamic_cast<Pacman*>(GameController::GetGameObjectManager().Get("Pacman"));
	if (pacman != NULL)
	{
		sf::Vector2f pacPos = pacman->GetPosition();
		timeBetweenMoves -= elapsed;
		SetColor(spriteColor.r, spriteColor.g, spriteColor.b);

		// Check ghost Win//Eaten
		if (collisionDetection(pacPos) && localMode == 3)
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
		else if (collisionDetection(pacPos) && localMode < 3)
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
					setGhostImage("assets/ghostCyan.png");
					frightened = false;
					pacPos = scatterMode(pacPos);
					break;
				case 2:							// Chase mode					
					if (blinky != NULL)
					{
						pacPos = chaseMode(pacPos, blinkyPos);
					}					
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


sf::Vector2f Inky::chaseMode(sf::Vector2f pacPos, sf::Vector2f blinkyPos)		// Chase Mode
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

	return pacPos;
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
