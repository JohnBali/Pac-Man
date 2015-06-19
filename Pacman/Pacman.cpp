#include "Pacman.h"

void Pacman::walk(Map map)
{
	sf::Vector2f pos = _sprite.getPosition();

	if (facing == RIGHT)
	{
		pos.x += this->GetSpeed();
		this->SetTile(pos);
		this->_sprite.setTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	}
	else if (facing == LEFT)
	{
		pos.x -= this->GetSpeed();
		this->SetTile(pos);
		this->_sprite.setTextureRect(sf::IntRect(left[frame] * 16, 0, 16, 16));
	}
	else if (facing == DOWN)
	{
		pos.y += this->GetSpeed();
		this->SetTile(pos);
		this->_sprite.setTextureRect(sf::IntRect(down[frame] * 16, 0, 16, 16));
	}
	else if (facing == UP)
	{
		pos.y -= this->GetSpeed();
		this->SetTile(pos);
		this->_sprite.setTextureRect(sf::IntRect(up[frame] * 16, 0, 16, 16));
	}
	_sprite.setPosition(pos);
	frame = (frame + 1) % 2;
}

void Pacman::Update(sf::Vector2f pacPos, sf::Time elapsed)
{
	timeBetweenMoves -= elapsed;
	if (timeBetweenMoves <= sf::Time::Zero)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (RowBoundary())
			{
				if (!map.isCollision(GetRow(), GetColumn() + 1))
				{
					SetFacing(Pacman::RIGHT);
					walk(map);
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (RowBoundary())
			{
				if (!map.isCollision(GetRow(), GetColumn() - 1))
				{
					SetFacing(Pacman::LEFT);
					walk(map);
				}
			}

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (ColumnBoundary())
			{
				if (!map.isCollision(GetRow() + 1, GetColumn()))
				{
					SetFacing(Pacman::DOWN);
					walk(map);
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (ColumnBoundary())
			{
				std::cout << "row:" << RowBoundary() << std::endl;

				if (!map.isCollision(GetRow() - 1, GetColumn()))
				{
					SetFacing(Pacman::UP);
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
		std::cout << "actual position: (" << GetPosition().x  << ", " << GetPosition().y << ")" << std::endl;
		std::cout << "grid position: (" << GetRow() << "," << GetColumn() << ")" << std::endl;
		std::cout << "map tile: " << map.getTile(GetRow(), GetColumn()) << std::endl;
}

Pacman::Pacman()
{
	//turn debug on or off
	debug = true;

	Load("assets/pacman.png");
	SetScale(2, 2);
	SetOrigin(4, 4);	
	GameObject::SetPosition(16, 16);
	SetTextureRect(sf::IntRect(right[frame] * 16, 0, 16, 16));
	SetSpeed(4);
	this->facing = RIGHT;
	timeBetweenMoves = sf::milliseconds(25);
}

Pacman::~Pacman()
{
}
