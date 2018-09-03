#include <GameObjectManager.hpp>
#include <Game.hpp>
#include <iostream>

GameObjectManager::GameObjectManager()
{}

GameObjectManager::~GameObjectManager()
{
      std::for_each(_objects.begin(),_objects.end(),GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject * object)
{
    this->_objects.insert(std::pair<std::string, VisibleGameObject *>(name, object));
}

void GameObjectManager::Remove(std::string name)
{
    std::map<std::string, VisibleGameObject *>::iterator results = this->_objects.find(name);
    if (results != this->_objects.end())
    {
        delete results->second;
        this->_objects.erase(results);
    }
}

VisibleGameObject * GameObjectManager::Get(std::string name) const
{
    std::map<std::string, VisibleGameObject *>::const_iterator results = this->_objects.find(name);
    if (results == this->_objects.end())
        return NULL;
    return results->second;
}

int GameObjectManager::GetObjectCount() const
{
    return this->_objects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow & window)
{
    std::map<std::string, VisibleGameObject *>::const_iterator results = this->_objects.begin();
    while (results != this->_objects.end())
    {
        results->second->Draw(window);
        results++;
    }
}

void GameObjectManager::UpdateAll()
{
    std::map<std::string,VisibleGameObject*>::const_iterator itr = _objects.begin();
    float timeDelta = this->clock.restart().asSeconds();

    while(itr != _objects.end())
    {
        itr->second->Update(timeDelta);
        itr++;
    }
}