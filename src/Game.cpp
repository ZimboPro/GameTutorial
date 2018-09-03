#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenu.hpp>
#include <PlayerPaddle.hpp>
#include <GameBall.hpp>

Game::GameState Game::_gameState = GameState::Uninitialized;
sf::RenderWindow Game::_window;
GameObjectManager Game::_manager;
int Game::SCREEN_HEIGHT = 764;
int Game::SCREEN_WIDTH = 1024;

Game::Game()
{}

Game::~Game()
{}

void Game::Start()
{
    if (_gameState != GameState::Uninitialized)
        return;
    
    _window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");
    _gameState = Game::ShowingSplash;

    PlayerPaddle * player1 = new PlayerPaddle();
    player1->Load("../resources/paddle.png");
    player1->SetPosition((1024 >> 1) - 45, 700);

    _manager.Add("Paddle1", player1);

    GameBall * ball = new GameBall();
    ball->SetPosition(SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1);

    _manager.Add("Ball", ball);

    while(!IsExiting())
    {
        GameLoop();
    }
    _window.close();
}

bool Game::IsExiting()
{
    if (_gameState == GameState::Exiting)
        return true;
    return false;
}

sf::RenderWindow & Game::GetWindow()
{
    return _window;
}

sf::Event Game::GetInput()
{
    sf::Event event;
    _window.pollEvent(event);
    return event;
}

void Game::GameLoop()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (_gameState)
        {
            case GameState::Playing:
            {
                _window.clear(sf::Color(0, 0, 0));
                _manager.UpdateAll();
                _manager.DrawAll(_window);
                _window.display();

                if (event.type == sf::Event::Closed)
                    _gameState = GameState::Exiting;
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                        ShowMainMenu();
                }
                break;
            }
            case GameState::ShowingSplash:
            {
                ShowSplashScreen();
                
                break;
            }
            case GameState::ShowingMenu:
            {
                ShowMainMenu();
                break;
            }
        }
    }
}

void Game::ShowSplashScreen()
{
    SplashScreen screen;
    screen.Show(_window);
    _gameState = GameState::ShowingMenu;
}

void Game::ShowMainMenu()
{
    MainMenu menu;
    MainMenu::MenuResult result = menu.Show(_window);
    switch(result)
    {
    case MainMenu::Exit:
        _gameState = Game::Exiting;
        break;
    case MainMenu::Play:
        _gameState = Game::Playing;
        break;
    }
}