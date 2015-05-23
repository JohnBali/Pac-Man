#include "GameObject.h"

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