#ifndef AIPADDLE_HPP
#define AIPADDLE_HPP

#include <VisibleGameObject.hpp>

class AIPaddle : public VisibleGameObject
{
    public:
        AIPaddle();
        ~AIPaddle();

        void Update(float elapsedTime);
        void Draw(sf::RenderWindow & window);

        float GetVelocity() const;
    
    private:
        float _velocity;
        float _maxVelocity;
};

#endif