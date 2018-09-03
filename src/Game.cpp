#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenu.hpp>
#include <PlayerPaddle.hpp>

Game::GameState Game::_gameState = GameState::Uninitialized;
sf::RenderWindow Game::_window;
GameObjectManager Game::_manager;

Game::Game()
{}

Game::~Game()
{}

void Game::Start()
{
    if (_gameState != GameState::Uninitialized)
        return;
    
    _window.create(sf::VideoMode(1024, 768, 32), "Pang!");
    _gameState = Game::ShowingSplash;

    PlayerPaddle * player1 = new PlayerPaddle();
    player1->Load("../resources/paddle.png");
    player1->SetPosition((1024 >> 1) - 45, 700);

    _manager.Add("Paddle1", player1);

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