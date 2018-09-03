#ifndef GAMEOBJECTMANAGER_HPP
#define GAMEOBJECTMANAGER_HPP

#include <VisibleGameObject.hpp>
#include <map>

class GameObjectManager
{
    public:
        GameObjectManager();
        ~GameObjectManager();

        void Add(std::string name, VisibleGameObject * object);
        void Remove(std::string name);
        int GetObjectCount() const;
        VisibleGameObject * Get(std::string name) const;

        void DrawAll(sf::RenderWindow & window);
        void UpdateAll();
    
    private:
        std::map<std::string, VisibleGameObject *> _objects;

        sf::Clock clock;

        struct GameObjectDeallocator
        {
            void operator()(const std::pair<std::string, VisibleGameObject *> & p) const
            {
                delete p.second;
            }
        };
};

#endif