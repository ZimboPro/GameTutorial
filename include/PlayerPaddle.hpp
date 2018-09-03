#ifndef PLAYERPADDLE_HPP
#define PLAYERPADDLE_HPP

#include <VisibleGameObject.hpp>

class PlayerPaddle : public VisibleGameObject
{
    public:
        PlayerPaddle();
        ~PlayerPaddle();

        void Update(float elapsedTime);
        void Draw(sf::RenderWindow & window);

        float GetVelocity() const;
    
    private:
        float _velocity;
        float _maxVelocity;
};

#endif