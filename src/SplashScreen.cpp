#include <SplashScreen.hpp>

#include <iostream>

void SplashScreen::Show(sf::RenderWindow & window)
{
    sf::Texture image;
    if (image.loadFromFile("../resources/Splashscreen.png") != true)
        return;
    
    sf::Sprite sprite(image);
    window.draw(sprite);
    window.display();

    while (true)
    {
        sf::Event event;
        window.pollEvent(event);
        if (event.type == sf::Event::EventType::KeyPressed || 
            event.type == sf::Event::EventType::MouseButtonPressed ||
            event.type == sf::Event::EventType::Closed)
            break;
    }
}