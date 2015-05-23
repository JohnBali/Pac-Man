#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, GameObject *gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	GameObject* Get(std::string name) const;

	void UpdateAll();
	void DrawAll(sf::RenderWindow &window);
	
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