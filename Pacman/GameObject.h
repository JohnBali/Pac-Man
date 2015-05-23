#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow &window);
	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition();
	virtual void GameObject::SetTexture(sf::Texture texture);
	virtual void GameObject::SetScale(float x, float y);
	virtual void GameObject::SetOrigin(float x, float y);
	virtual void GameObject::SetTextureRect(sf::IntRect rect);

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;
};