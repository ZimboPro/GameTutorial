#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GameObjectManager.hpp>

class Game
{
    public:
        static void Start();
        static sf::RenderWindow & GetWindow();
        static sf::Event GetInput();
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;

    private:
        Game();
        ~Game();

        static bool IsExiting();
        static void GameLoop();

        static void ShowSplashScreen();
        static void ShowMainMenu();

        enum GameState { Uninitialized, ShowingSplash, Paused, 
          ShowingMenu, Playing, Exiting };
        
        static GameState _gameState;
        static sf::RenderWindow _window;
        static GameObjectManager _manager;
};

#endif