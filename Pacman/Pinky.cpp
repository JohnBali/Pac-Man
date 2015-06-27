#include "Pinky.h"

// Set the path
void Pinky::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing pacFacing, sf::Vector2f blinkyPos, int ghostMode, int &score)
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
				// Mode and path switch
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
					pacPos.x = (float)this->getScatterTile().x * 16;
					pacPos.y = (float)this->getScatterTile().y * 16;
					this->walk(pacPos);
					break;
				case 2:							// Chase mode
					if (frightened)
						setGhostColor();
					this->SetSpeed(4);
					switch (pacFacing)
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

void Pinky::setGhostColor()
{
	Load("assets/ghostPink.png");
	SetScale(2, 2);
	SetOrigin(4, 4);

}

// Constructors
Pinky::Pinky()
{
	//turn debug on or off
	debug = false;
	frightened = false;

	setGhostColor();
	SetFacing(LEFT);

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
