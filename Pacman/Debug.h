#pragma once
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Map.h"

class Debug : public GameObject
{
public:
	Debug(GameObjectManager &gameObjectManager);
	void Draw(sf::RenderWindow &window);

private:
	GameObjectManager _gameObjectManager;
	static Map* _map;	
};