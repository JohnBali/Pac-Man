#include "Ghostclass.h"
#include "VectorMath.h"

// Walk
void Ghostclass::walk(sf::Vector2f pacPos)
{
	float target = 0.0;
	float distance = 0.0;
	sf::Vector2i pos = sf::Vector2i(GetRow(), GetColumn());
	sf::Vector2i prev = this->getPrevTile();
	std::vector<sf::Vector2i> exits = map->getExits(pos.x, pos.y);
	std::vector<sf::Vector2i>::iterator it;

	if (RowBoundary() && ColumnBoundary())
	{
		for (it = exits.begin(); it != exits.end(); it++)
		{
			if (it->x == prev.x && it->y == prev.y);
			else
			{
				distance = vm::magnitude(sf::Vector2f(it->x*16 - pacPos.x, it->y*16 - pacPos.y));
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
		this->_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	}
	else if (facing == LEFT)
	{
		ghostPos.x -= this->GetSpeed();
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

void Ghostclass::setPrevTile(sf::Vector2i pos)
{
	this->previousTile = pos;
}

sf::Vector2i Ghostclass::getPrevTile()
{
	return this->previousTile;
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

void Ghostclass::setMode(int mode)
{
	this->mode = mode;
}

int Ghostclass::getMode()
{
	return this->mode;
}

Ghostclass::Ghostclass()
{}

Ghostclass::~Ghostclass()
{}

void Ghostclass::Debug(std::vector<sf::Vector2i> exits)
{
	std::cout << std::endl; 
	std::cout << "<<< Blinkys' Data >>>" << std::endl;
	std::cout << "Blinky's position: (" << GetPosition().x << ", " << GetPosition().y << ")" << std::endl;
	std::cout << "grid position: (" << GetRow() << "," << GetColumn() << ")" << std::endl;
	std::cout << "map tile: " << map->getTile(GetRow(), GetColumn()) << std::endl;
	std::cout << std::endl;
	std::cout << "Set tile: " << GetTile().x << ", " << GetTile().y << std::endl;
	std::cout << "Next tile: " << getNextTile().x << ", " << getNextTile().y << std::endl;
	std::cout << "Previous tile: " << getPrevTile().x << ", " << getPrevTile().y << std::endl;
	std::cout << std::endl;
	std::vector<sf::Vector2i>::iterator it;

	for (it = exits.begin(); it != exits.end(); it++)
	{
		std::cout << "Exit: " << it->x << ", " << it->y << ": Map tile: " << map->getTile(it->x, it->y) << std::endl;
	}
	std::cout << std::endl;
	std::cout << "<<< Blinkys' Data END >>>" << std::endl;
	std::cout << std::endl;
}