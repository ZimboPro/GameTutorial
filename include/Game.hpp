#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
    public:
        static void Start();

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
};

#endif