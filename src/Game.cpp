#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenu.hpp>

Game::GameState Game::_gameState = GameState::Uninitialized;
sf::RenderWindow Game::_window;

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
                _window.clear(sf::Color(255, 0, 0));
                _window.display();

                if (event.type == sf::Event::Closed)
                    _gameState = GameState::Exiting;
                break;
            }
            case GameState::ShowingSplash:
            {
                ShowSplashScreen();
                _gameState = GameState::ShowingMenu;
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
    _gameState = ShowingSplash;
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