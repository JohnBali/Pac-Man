#include "GameObject.h"
#include "Map.h"

const int GameObject::left[FRAMES] = { 6, 7, 8 };
const int GameObject::right[FRAMES] = { 3, 4, 5 };
const int GameObject::down[FRAMES] = { 0, 1, 2 };
const int GameObject::up[FRAMES] = { 9, 10, 11 };


GameObject::GameObject()
	: _isLoaded(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::Load(std::string filename)
{
	if (!_texture.loadFromFile(filename))
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void GameObject::Draw(sf::RenderWindow &window)
{
	if (_isLoaded)
	{
		window.draw(_sprite);
	}
}

void GameObject::SetTexture(sf::Texture texture)
{
	_sprite.setTexture(texture);
}

void GameObject::SetScale(float x, float y)
{
	_sprite.setScale(x, y);
}

void GameObject::SetOrigin(float x, float y)
{
	_sprite.setOrigin(x, y);
}

void GameObject::SetTextureRect(sf::IntRect rect)
{
	_sprite.setTextureRect(rect);
}

void GameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

sf::Vector2f GameObject::GetPosition()
{
	return _sprite.getPosition();
}

void GameObject::Update()
{

}

// Merge of GameObject and Spriteclass

void GameObject::SetFacing(Facing facing)
{
	this->facing = facing;
}

GameObject::Facing GameObject::GetFacing()
{
	return this->facing;
}


void GameObject::SetTile(sf::Vector2f pos)
{
	this->tile.x = (int)pos.x / 16;
	this->tile.y = (int)pos.y / 16;
}

sf::Vector2i GameObject::GetTile()
{
	return this->tile;
}

void GameObject::SetSpeed(float speed)
{
	this->speed = speed;
}

float GameObject::GetSpeed()
{
	return this->speed;
}

bool GameObject::RowBoundary()
{
	return ((int)_sprite.getPosition().y % 16 == 0);
}
bool GameObject::ColumnBoundary()
{
	return ((int)_sprite.getPosition().x % 16 == 0);
}

int GameObject::GetColumn()
{
	return _sprite.getPosition().y / 16;
}

int GameObject::GetRow()
{
	return _sprite.getPosition().x / 16;
}
