#include <GameBall.hpp>
#include <cassert>

GameBall::GameBall()
{
    Load("../resources/ball.png");
    assert(IsLoaded());

    GetSprite().setOrigin(15, 15);
}

GameBall::~GameBall()
{}