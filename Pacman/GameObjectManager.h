#pragma once
#include "GameObject.h"
#include "Map.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, GameObject *gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	GameObject* Get(std::string name) const;

	void UpdateAll(sf::Vector2f pacPos, sf::Time elapsed);
	void DrawAll(sf::RenderWindow &window);
	sf::Vector2f GetPosition(std::string name);
	
private:
	std::map<std::string, GameObject*> _gameObjects;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, GameObject*> & p) const
		{
			delete p.second;
		}
	};
};