#include <GameBall.hpp>
#include <cassert>
#include <SFML/System.hpp>
#include <Game.hpp>
#include <PlayerPaddle.hpp>
#include <cmath>
#include <iostream>

GameBall::GameBall() : _velocity(230.0f), _elapsedTimeSinceStart(0.0f)
{
    Load("../resources/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15, 15);

    srand(time(NULL));
    this->_angle = static_cast<float>(rand() % 360 + 1);
}

GameBall::~GameBall()
{}

void GameBall::Update(float timeElapsed)
{
    this->_elapsedTimeSinceStart += timeElapsed;

    if (this->_elapsedTimeSinceStart < 3.0f)
        return;


    float moveAmount = _velocity * timeElapsed;

    float moveByX = LinearVelocityX(this->_angle) * moveAmount;
    float moveByY = LinearVelocityY(this->_angle) * moveAmount;

    if (GetPosition().x + moveByX <= 0 + GetWidth() / 2 || GetPosition().x + GetWidth() / 2 + moveByX >= Game::SCREEN_WIDTH)
    {
        std::cout << "rebound  wall" << std::endl;
        _angle = 360.0f - _angle;
        if(_angle > 260.0f && _angle < 280.0f)
            _angle += 20.0f;
        if(_angle > 80.0f && _angle < 100.0f)
            _angle += 20.0f;
        moveByX = -moveByX;
    }

    PlayerPaddle * player1 = dynamic_cast<PlayerPaddle *>(Game::GetGameObjectManager().Get("Paddle1"));
    if (player1 != NULL)
    {
        sf::Rect<float> p1BB = player1->GetBoundingRect();

        if (p1BB.intersects(GetBoundingRect()))
        {
            sf::Rect<float> bBB = GetBoundingRect();
            _angle = 360.0f - (_angle - 180.f);
            if (_angle > 360.0f)
                _angle -= 360.f;
            
            moveByY = -moveByY;

            if (GetBoundingRect().top - GetBoundingRect().height > player1->GetBoundingRect().top)
                SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth() / 2  - 1);
            
            float playerVelocity = player1->GetVelocity();
    
            if(playerVelocity < 0)
            {
                // moving left
                _angle -= 20.0f;
                if(_angle < 0 )
                    _angle = 360.0f - _angle;
            }
            else if(playerVelocity > 0)
            {
                _angle += 20.0f;
                if(_angle > 360.0f)
                    _angle = _angle - 360.0f;
            }

            _velocity += 5.0f;
        }

        if(GetPosition().y - GetHeight()/2 <= 0)
        {
            _angle =  180 - _angle;
            moveByY = -moveByY;
        }
        
        if(GetPosition().y + GetHeight()/2 + moveByY >= Game::SCREEN_HEIGHT)
        {
            // move to middle of the screen for now and randomize angle
            GetSprite().setPosition(Game::SCREEN_WIDTH/2, Game::SCREEN_HEIGHT/2);
            _angle = static_cast<float>(rand() % 360);
            _velocity = 220.0f;
            _elapsedTimeSinceStart = 0.0f;
        }

        GetSprite().move(moveByX,moveByY);
    }
}

float GameBall::LinearVelocityX(float angle)
{
    angle -= 90;
    if (angle < 0)
        angle = 360 + angle;
    return (float)std::cos( angle * ( 3.1415926 / 180.0f ));
}

float GameBall::LinearVelocityY(float angle)
{
    angle -= 90;
    if (angle < 0)
        angle = 360 + angle;
    return (float)std::sin( angle * ( 3.1415926 / 180.0f ));
}
