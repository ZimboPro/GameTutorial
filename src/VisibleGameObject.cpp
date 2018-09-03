#include <VisibleGameObject.hpp>

VisibleGameObject::VisibleGameObject()
{
    this->_isLoaded = false;
}

VisibleGameObject::~VisibleGameObject()
{}

void VisibleGameObject::Load(std::string filename)
{
    if (_image.loadFromFile(filename) == false)
    {
        this->_filename = "";
        this->_isLoaded = false;
    }
    else
    {
        this->_filename = filename;
        this->_sprite.setTexture(this->_image);
        this->_isLoaded = true;
    }
}

void VisibleGameObject::Draw(sf::RenderWindow & window)
{
    if (this->_isLoaded)
        window.draw(this->_sprite);
}

void VisibleGameObject::SetPosition(float x, float y)
{
    if (this->_isLoaded)
    {
        this->_sprite.setPosition(x, y);
    }
}