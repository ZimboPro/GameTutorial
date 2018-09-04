#include <Game.hpp>
#include <SplashScreen.hpp>
#include <MainMenu.hpp>
#include <PlayerPaddle.hpp>
#include <GameBall.hpp>
#include <ServiceLocator.hpp>
#include <SFMLSoundProvider.hpp>
#include <AIPaddle.hpp>

Game::GameState Game::_gameState = GameState::Uninitialized;
sf::RenderWindow Game::_window;
sf::Event Game::_event;
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

    AIPaddle * player2 = new AIPaddle();
    player2->SetPosition((SCREEN_WIDTH/2),40);

    PlayerPaddle * player1 = new PlayerPaddle();
    player1->Load("../resources/paddle.png");
    player1->SetPosition((1024 >> 1) - 45, 700);

    _manager.Add("Paddle1", player1);
    _manager.Add("Paddle2", player2);

    GameBall * ball = new GameBall();
    ball->SetPosition(SCREEN_WIDTH >> 1, SCREEN_HEIGHT >> 1);

    _manager.Add("Ball", ball);

    SFMLSoundProvider sound;
    ServiceLocator::RegisterServiceLocator(&sound);

    while(!IsExiting())
    {
        GameLoop();
    }
    ServiceLocator::GetAudio()->StopAllSounds();
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
    return _event;
}

void Game::GameLoop()
{
    _window.pollEvent(_event);
    switch (_gameState)
    {
        case GameState::Playing:
        {
            _window.clear(sf::Color(0, 0, 0));
            _manager.UpdateAll();
            _manager.DrawAll(_window);
            _window.display();

            if (_event.type == sf::Event::Closed)
                _gameState = GameState::Exiting;
            if (_event.type == sf::Event::KeyPressed)
            {
                if (_event.key.code == sf::Keyboard::Escape)
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
    ServiceLocator::GetAudio()->StopAllSounds();
}

GameObjectManager & Game::GetGameObjectManager()
{
    return _manager;
}