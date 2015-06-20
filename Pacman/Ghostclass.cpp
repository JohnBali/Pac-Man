#include "Ghostclass.h"
#include "VectorMath.h"

// Walk
void Ghostclass::walk(Map &map, sf::Vector2f pacPos)
{
	if (this->RowBoundary() && this->ColumnBoundary())
	{
		float target = 0.0;
		sf::Vector2i pos = this->GetTile();
		sf::Vector2i prev = this->getPrevTile();
		std::vector<sf::Vector2i> exits = map.getExits(pos.x, pos.y);
		std::vector<sf::Vector2i>::iterator it;

		for (it = exits.begin(); it != exits.end(); it++)
		{
			if (it->x != prev.x && it->y != prev.y);
			{
				float distance = vm::magnitude(sf::Vector2f(it->x - pacPos.x, it->y - pacPos.y));
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
			this->SetFacing(Ghostclass::LEFT);
		else if (pos.x == 1)
			this->SetFacing(Ghostclass::RIGHT);
		else if (pos.y == 1)
			this->SetFacing(Ghostclass::DOWN);
		else if (pos.y == -1)
			this->SetFacing(Ghostclass::UP);
	}

	// Walk the path
	sf::Vector2f pos = this->GetPosition();
	if (facing == RIGHT)
	{
		pos.x += this->GetSpeed();
		this->SetTile(pos);
		this->setPrevTile(sf::Vector2i(this->GetTile().x - 1, this->GetTile().y));
		this->_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	}
	else if (facing == LEFT)
	{
		pos.x -= this->GetSpeed();
		this->SetTile(pos);
		this->setPrevTile(sf::Vector2i(this->GetTile().x + 1, this->GetTile().y));
		this->_sprite.setTextureRect(sf::IntRect(left[frame] * 16, 0, 16, 16));
	}
	else if (facing == DOWN)
	{
		pos.y += this->GetSpeed();
		this->SetTile(pos);
		this->setPrevTile(sf::Vector2i(this->GetTile().x, this->GetTile().y - 1));
		this->_sprite.setTextureRect(sf::IntRect(down[frame] * 16, 0, 16, 16));
	}
	else if (facing == UP)
	{
		pos.y -= this->GetSpeed();
		this->SetTile(pos);
		this->setPrevTile(sf::Vector2i(this->GetTile().x, this->GetTile().y + 1));
		this->_sprite.setTextureRect(sf::IntRect(up[frame] * 16, 0, 16, 16));
	}
	_sprite.setPosition(pos);
	frame = (frame + 1) % 3;
}
// Setters/Getters
void Ghostclass::setPrevPosition(sf::Vector2f pos)
{
	this->previousPosition = pos;
}

sf::Vector2f Ghostclass::getPrevPosition()
{
	return this->previousPosition;
}

void Ghostclass::setNextPosition(sf::Vector2f pos)
{
	this->nextPosition = pos;
}

sf::Vector2f Ghostclass::getNextPosition()
{
	return this->nextPosition;
}

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