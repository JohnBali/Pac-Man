#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

const int FRAMES = 3;

class GameObject
{
public:
	enum Facing
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	GameObject();
	virtual ~GameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow &window);
	virtual void Update(sf::Vector2f pacPos, sf::Time elapsed);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition();
	virtual void GameObject::SetTexture(sf::Texture texture);
	virtual void GameObject::SetScale(float x, float y);
	virtual void GameObject::SetOrigin(float x, float y);
	virtual void GameObject::SetTextureRect(sf::IntRect rect);

	void SetFacing(Facing facing);
	Facing GetFacing();

	void SetTile(sf::Vector2f pos);
	sf::Vector2i GetTile();

	void SetSpeed(float speed);
	float GetSpeed();

	bool RowBoundary();
	bool ColumnBoundary();

	int GetColumn();
	int GetRow();

protected:
	Facing facing;

	int frame = 0;
	float speed = 4;
	sf::Vector2i tile;

	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename;
	bool _isLoaded;

	static const int left[FRAMES];
	static const int right[FRAMES];
	static const int down[FRAMES];
	static const int up[FRAMES];

};