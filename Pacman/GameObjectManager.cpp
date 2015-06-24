#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, GameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, GameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, GameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

GameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, GameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;
}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}

void GameObjectManager::UpdateAll(sf::Vector2f pacPos, sf::Time elapsed, GameObject::Facing facing, sf::Vector2f blinkyPos)
{
	std::map<std::string, GameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Update(pacPos, elapsed, facing, blinkyPos);
		itr++;
	}
}

void GameObjectManager::DrawAll(sf::RenderWindow &window)
{
	std::map<std::string, GameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(window);
		itr++;
	}
}

