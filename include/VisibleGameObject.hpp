#ifndef VISIBLEGAMEOBJECT_HPP
#define VISIBLEGAMEOBJECT_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class VisibleGameObject
{
    public:
        VisibleGameObject();
        virtual ~VisibleGameObject();

        virtual void Load(std::string filename);
        virtual void Draw(sf::RenderWindow & window);
        virtual void Update(float eplasedTime);

        virtual void SetPosition(float x, float y);
        virtual sf::Vector2f GetPosition() const;
        virtual bool IsLoaded() const;

        virtual float GetWidth() const;
        virtual float GetHeight() const;

        virtual sf::Rect<float> GetBoundingRect() const;

    protected:
        sf::Sprite & GetSprite();

    private:
        sf::Sprite  _sprite;
        sf::Texture _image;
        std::string _filename;
        bool _isLoaded;
};

#endif