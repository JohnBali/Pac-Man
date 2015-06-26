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
		sf::Image pacmanImage = _texture.copyToImage();
		pacmanImage.createMaskFromColor(sf::Color(0, 0, 0), 0);

		if (!_texture.loadFromImage(pacmanImage))
		{
			std::cout << "Error masking image resource pacman.png" << std::endl;
		}
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

void GameObject::Update(sf::Vector2f pacPos, sf::Time elapsed, Facing facing, sf::Vector2f blinkyPos, int ghostMode, int &score)
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


void GameObject::SetTile()
{
	this->tile.x = GetRow();
	this->tile.y = GetColumn();
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
	return (int)_sprite.getPosition().x / 16;
}

int GameObject::GetRow()
{
	return (int)_sprite.getPosition().y / 16;
}

void GameObject::SetWin()
{
	ghostWin = true;
}

bool GameObject::GetWin()
{
	return ghostWin;
}

void GameObject::setMode(int mode)
{
	this->ghostMode = mode;
}

int GameObject::getMode()
{
	return this->ghostMode;
}

