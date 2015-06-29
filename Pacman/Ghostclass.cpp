/**
* Developer: Team Six Pack
* Game Name: Pacman
* Description: This is Ghostclass class. This class manages the operations of all ghosts.
*/

#include "Ghostclass.h"

// Walk
void Ghostclass::walk(sf::Vector2f pacPos)
{
	// set variables
	float target = 0.0;
	float distance = 0.0;
	sf::Vector2f posPac;		// Need to switch coordinates to work with the map coordinate system
	posPac.x = pacPos.y;
	posPac.y = pacPos.x;
	sf::Vector2i pos = sf::Vector2i(GetRow(), GetColumn());
	std::vector<sf::Vector2i> exits = map->getExits(pos.x, pos.y);
	std::vector<sf::Vector2i>::iterator it;

	if (RowBoundary() && ColumnBoundary())
	{
		for (it = exits.begin(); it != exits.end(); it++)
		{
			sf::Vector2i prev;
			prev.x = it->x;
			prev.y = it->y;
			if (checkPrevTile(prev));
			else
			{
				distance = vm::magnitude(sf::Vector2f(it->x * 16 - posPac.x, it->y * 16 - posPac.y));
				if (target == 0.0)
				{
					target = distance;
					setNextTile(sf::Vector2i(it->x, it->y));
				}
				else if (distance < target)
				{
					target = distance;
					setNextTile(sf::Vector2i(it->x, it->y));
				}
			}
		}
		// Set facing to next tile
		pos -= nextTile;
		if (pos.x == -1)
			this->SetFacing(Ghostclass::DOWN);
		else if (pos.x == 1)
			this->SetFacing(Ghostclass::UP);
		else if (pos.y == 1)
			this->SetFacing(Ghostclass::LEFT);
		else if (pos.y == -1)
			this->SetFacing(Ghostclass::RIGHT);

	}

	// Walk the path
	sf::Vector2f ghostPos = this->GetPosition();
	if (facing == RIGHT)
	{
		ghostPos.x += this->GetSpeed();
		// Go through side gate (buggy)
		if (GetColumn() > 27)
			ghostPos.x = -32;
		this->_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	}
	else if (facing == LEFT)
	{
		ghostPos.x -= this->GetSpeed();
		// Go through side gate (buggy)
		if (GetColumn() < 0)
			ghostPos.x = 448;
		this->_sprite.setTextureRect(sf::IntRect(left[frame] * 16, 0, 16, 16));
	}
	else if (facing == DOWN)
	{
		ghostPos.y += this->GetSpeed();
		this->_sprite.setTextureRect(sf::IntRect(down[frame] * 16, 0, 16, 16));
	}
	else if (facing == UP)
	{
		ghostPos.y -= this->GetSpeed();
		this->_sprite.setTextureRect(sf::IntRect(up[frame] * 16, 0, 16, 16));
	}

	// Set Sprite position
	_sprite.setPosition(ghostPos);
	frame = (frame + 1) % 3;

	// Set tiles
	sf::Vector2i tilepos = sf::Vector2i(GetRow(), GetColumn());
	if (tilepos == getNextTile())
	{
		setPrevTile(GetTile());
		SetTile();
	}

	// Debugging
	if (this->debug)
	{
		Debug(exits);
	}

}
// Setters/Getters
void Ghostclass::setMode(int mode)
{
	this->ghostMode = mode;
}

int Ghostclass::getMode()
{
	return this->ghostMode;
}

void Ghostclass::SetEaten(bool state)
{
	ghostEaten = state;
}

bool Ghostclass::GetEaten()
{
	return ghostEaten;
}

void Ghostclass::SetWin()
{
	ghostWin = true;
}

bool Ghostclass::GetWin()
{
	return ghostWin;
}

void Ghostclass::setPrevTile(sf::Vector2i pos)
{
	for (int i = 6; i > 0; i--)
	{
		previousTile[i] = previousTile[i - 1];
	}
	previousTile[0] = pos;
}

sf::Vector2i Ghostclass::getPrevTile()
{
	return this->previousTile[0];
}

bool Ghostclass::checkPrevTile(sf::Vector2i pos)
{
	bool valid = false;
	for (int i = 0; i < 6; i++)
	{
		if (pos.x == previousTile[i].x && pos.y == previousTile[i].y)
			valid = true;
	}

	return valid;
}

void Ghostclass::clearPrevTiles()
{
	for (int i = 0; i< 6; i++)
	{
		previousTile[i] = sf::Vector2i(0, 0);
	}
}

void Ghostclass::setNextTile(sf::Vector2i pos)
{
	this->nextTile = pos;
}

sf::Vector2i Ghostclass::getNextTile()
{
	return this->nextTile;
}

void Ghostclass::setScatterTile(sf::Vector2i pos)
{
	this->scatterTile = pos;
}

sf::Vector2i Ghostclass::getScatterTile()
{
	return this->scatterTile;
}

void Ghostclass::modeSwitch()
{
	clearPrevTiles();
	Facing facing = GetFacing();
	switch (facing)
	{
	case GameObject::LEFT:
		SetFacing(RIGHT);
		break;
	case GameObject::RIGHT:
		SetFacing(LEFT);
		break;
	case GameObject::UP:
		SetFacing(DOWN);
		break;
	case GameObject::DOWN:
		SetFacing(UP);
		break;
	}
}

sf::Vector2i Ghostclass::frightExits()
{
	// Variables
	sf::Vector2i pos = sf::Vector2i(GetRow(), GetColumn());
	std::vector<sf::Vector2i> exits = map->getExits(pos.x, pos.y); 
	int sze = exits.size();
	int random_int = rand()%sze;
	pos = exits[random_int];

	return pos;
}

void Ghostclass::setGhostBlue()
{
	Load("assets/ghostFright.png");
	SetScale(2, 2);
	SetOrigin(4, 4);
}

void Ghostclass::setGhostEyes()
{
	Load("assets/ghostEyes.png");
	SetScale(2, 2);
	SetOrigin(4, 4);
}

bool Ghostclass::ghostHouse()
{
	if (GetColumn() > 10 && GetColumn() < 17 && GetRow() < 15 && GetRow() >11)
		return true;
	return false;
}

bool Ghostclass::ghostHouseTwo()
{
	if (GetColumn() > 10 && GetColumn() < 17 && GetRow() < 15 && GetRow() >13)
		return true;
	return false;
}

sf::Vector2f Ghostclass::stoppedMode(sf::Vector2f pacPos)	// Stopped
{
	this->SetSpeed(0);

	return pacPos;
}

sf::Vector2f Ghostclass::scatterMode(sf::Vector2f pacPos)		// Scatter Mode
{
	this->SetSpeed(4);
	pacPos.x = (float)this->getScatterTile().x * 16;
	pacPos.y = (float)this->getScatterTile().y * 16;

	return pacPos;
}

sf::Vector2f Ghostclass::frightMode(sf::Vector2f pacPos)			// Fright Mode
{
	this->SetSpeed(2);
	setGhostBlue();
	frightened = true;
	if (RowBoundary() && ColumnBoundary())
	{
		sf::Vector2i runaway = frightExits();
		pacPos.x = (float)runaway.x;
		pacPos.y = (float)runaway.y;
	}

	return pacPos;
}

sf::Vector2f Ghostclass::eyeMode(sf::Vector2f pacPos)			// Eye Mode
{
	this->SetSpeed(4);
	setGhostEyes();
	pacPos = (sf::Vector2f(224, 224));
	if (ghostHouseTwo())
	{
		setMode(1);
		this->localMode = 1;
		SetEaten(false);
	}

	return(pacPos);
}

void Ghostclass::setGhostImage(std::string filename)
{
	Load(filename);
	SetScale(2, 2);
	SetOrigin(4, 4);

}

Ghostclass::Ghostclass()
{}

Ghostclass::~Ghostclass()
{}

void Ghostclass::Debug(std::vector<sf::Vector2i> exits)
{
	std::cout << std::endl; 
	std::cout << "<<< Ghosts' Data >>>" << std::endl;
	std::cout << "Ghosts' position: (" << GetPosition().x << ", " << GetPosition().y << ")" << std::endl;
	std::cout << "grid position: (" << GetRow() << "," << GetColumn() << ")" << std::endl;
	std::cout << "map tile: " << map->getTile(GetRow(), GetColumn()) << std::endl;
	std::cout << std::endl;
	std::cout << "Set tile: " << GetTile().x << ", " << GetTile().y << std::endl;
	std::cout << "Next tile: " << getNextTile().x << ", " << getNextTile().y << std::endl;

	for (int i = 0; i < 6; i++)
	{
		std::cout << "Previous tile " << i << ": " << previousTile[i].x << ", " << previousTile[i].y << std::endl;
	}
	
	
	std::cout << std::endl;
	std::vector<sf::Vector2i>::iterator it;

	for (it = exits.begin(); it != exits.end(); it++)
	{
		std::cout << "Exit: " << it->x << ", " << it->y << ": Map tile: " << map->getTile(it->x, it->y) << std::endl;
	}
	std::cout << std::endl;
	std::cout << "<<< Ghost Data END >>>" << std::endl;
	std::cout << std::endl;
}