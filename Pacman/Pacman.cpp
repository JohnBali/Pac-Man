#include "Pacman.h"

void Pacman::walk(Map* map)
{
	sf::Vector2f pos = _sprite.getPosition();

	if (facing == RIGHT)
	{
		pos.x += this->GetSpeed();

		//this code cause pacman to wrap around to the other side of the screen when going through the right side gate
		if (GetColumn() < 29)
		{
		}
		else
		{
			pos.x = -32;
		}
		this->_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	}
	else if (facing == LEFT)
	{
		pos.x -= this->GetSpeed();

		//this code cause pacman to wrap around to the other side of the screen when going through the left side gate
		if (GetColumn() >= -1)
		{
		}
		else
		{
			pos.x = 448;
		}
		
		this->_sprite.setTextureRect(sf::IntRect(left[frame] * 16, 0, 16, 16));
	}
	else if (facing == DOWN)
	{
		pos.y += this->GetSpeed();
		this->_sprite.setTextureRect(sf::IntRect(down[frame] * 16, 0, 16, 16));
	}
	else if (facing == UP)
	{
		pos.y -= this->GetSpeed();
		this->_sprite.setTextureRect(sf::IntRect(up[frame] * 16, 0, 16, 16));
	}
	_sprite.setPosition(pos);
	SetTile();
	frame = (frame + 1) % 3;
}

void Pacman::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if ((!map->isCollision(GetRow(), GetColumn() + 1) || !ColumnBoundary() || (GetColumn() >= 27 || GetColumn() < 0)) && RowBoundary())
		{
			SetFacing(Pacman::RIGHT);
		}		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if ((!map->isCollision(GetRow(), GetColumn() - 1) || !ColumnBoundary() || (GetColumn() - 1) < 0) && RowBoundary())
		{
			SetFacing(Pacman::LEFT);
		}		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if ((!map->isCollision(GetRow() + 1, GetColumn()) || !RowBoundary()) && ColumnBoundary())
		{
			SetFacing(Pacman::DOWN);
		}		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if ((!map->isCollision(GetRow() - 1, GetColumn()) || !RowBoundary()) && ColumnBoundary())
		{
			SetFacing(Pacman::UP);
		}		
	}

	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		if (GetFacing() == Pacman::RIGHT)
		{
			if (RowBoundary())
			{
				if (!map->isCollision(GetRow(), GetColumn() + 1) || !ColumnBoundary() || (GetColumn() >= 27 || GetColumn() < 0))
				{
					walk(map);
				}
			}
		}
		else if (GetFacing() == Pacman::LEFT)
		{
			if (RowBoundary())
			{
				if (!map->isCollision(GetRow(), GetColumn() - 1) || !ColumnBoundary() || (GetColumn() - 1) < 0)
				{
					walk(map);
				}
			}

		}
		else if (GetFacing() == Pacman::DOWN)
		{
			if (ColumnBoundary())
			{
				if (!map->isCollision(GetRow() + 1, GetColumn()) || !RowBoundary())
				{
					walk(map);
				}
			}
		}
		else if (GetFacing() == Pacman::UP)
		{
			if (ColumnBoundary())
			{
				std::cout << "row:" << RowBoundary() << std::endl;

				if (!map->isCollision(GetRow() - 1, GetColumn()) || !RowBoundary())
				{
					walk(map);
				}
			}
		}
		timeBetweenMoves = sf::milliseconds(25);

		if (debug)
		{
			Debug();
		}
	}
}

void Pacman::Debug()
{
	std::cout << std::endl;
	std::cout << "<<< Pacmans' Data >>>" << std::endl;
	std::cout << "actual position: (" << GetPosition().x  << ", " << GetPosition().y << ")" << std::endl;
	std::cout << "grid position: (" << GetRow() << "," << GetColumn() << ")" << std::endl;
	std::cout << "map tile: " << map->getTile(GetRow(), GetColumn()) << std::endl;
	std::cout << std::endl;
	std::cout << "<<< END Pacmans' Data >>>" << std::endl;
	std::cout << std::endl;
}

Pacman::Pacman()
{
	//turn debug on or off
	debug = false;

	Load("assets/pacman.png");
	SetScale(2, 2);
	SetOrigin(4, 4);	
	GameObject::SetPosition(216, 368);
	SetTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetSpeed(4);
	this->facing = RIGHT;
	timeBetweenMoves = sf::milliseconds(25);
}

Pacman::~Pacman()
{
}
