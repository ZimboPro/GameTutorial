#include <PlayerPaddle.hpp>
#include <cassert> 
#include <Game.hpp>

PlayerPaddle::PlayerPaddle() : _velocity(0.0f), _maxVelocity(600.0f)
{
    Load("../resources/paddle.png");
    assert(IsLoaded());

    GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle()
{}

void PlayerPaddle::Draw(sf::RenderWindow & window)
{
    VisibleGameObject::Draw(window);
}

float PlayerPaddle::GetVelocity() const
{
    return this->_velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        _velocity -= 3.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        _velocity += 3.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        _velocity = 0.0f;
    
    if (_velocity > _maxVelocity)
        _velocity = _maxVelocity;
    if (_velocity < -_maxVelocity)
        _velocity = -_maxVelocity;
    
    sf::Vector2f pos = this->GetPosition();
    if(pos.x  < GetSprite().getLocalBounds().width/2
		|| pos.x > (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width/2))
	{
		_velocity = -_velocity;
	}
    GetSprite().move(_velocity * elapsedTime, 0);
}