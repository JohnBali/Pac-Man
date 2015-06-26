#include "Inky.h"

// Set the path
void Inky::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		// Variables
		int localMode = ghostMode;
		sf::Vector2f temp = pacPos;

		if (score < 30)
			localMode = 0;
		
		if (getMode() != localMode)
		{
			setMode(localMode);
			modeSwitch();
		}


		// Check ghost Win
		if (pacPos.x / 16 == GetColumn() && pacPos.y / 16 == GetRow())
			SetWin();

		if (!GetWin())
		{
			// Test if ghost is in ghost house
			if (GetColumn() > 10 && GetColumn() < 17 && GetRow() < 15 && GetRow() > 11 && localMode != 0)
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
					this->SetSpeed(0);
					this->walk(pacPos);
					break;
				case 1:							// Scatter mode
					this->SetSpeed(4);
					pacPos.x = (float)this->getScatterTile().x * 16;
					pacPos.y = (float)this->getScatterTile().y * 16;
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
				case 3:							/// Frightened mode
					this->SetSpeed(2);
					_sprite.setColor(sf::Color(16, 32, 128));
					sf::Vector2i runaway = frightMode();
					pacPos.x = (float)runaway.x;
					pacPos.y = (float)runaway.y;
					this->walk(pacPos);
					break;
				}
			}
			timeBetweenMoves = sf::milliseconds(25);
		}
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
