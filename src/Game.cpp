#include "Game.h"

Game::Game() : isPlaying(true)
{
    vector <sf::VideoMode> vMode = sf::VideoMode::getFullscreenModes();
    window.create(vMode[0], "Shootan", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
}

Game::~Game()
{
    //dtor
}

void Game::play()
{
    GameObject* player = new Player;
    clock = new sf::Clock;
    while (isPlaying)
    {
        frameTime = clock->restart().asSeconds();
        ProcessEvents();
        player->update();
        window.clear(sf::Color(235, 235, 235));
        window.draw(*player);
        window.display();
    }
}

void Game::ProcessEvents(){
    sf::Event event;
    while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code==sf::Keyboard::Escape)
                    {
                    window.close();
                    isPlaying = false;
                    return;
                    }
                break;
            default:
                break;
            }
        }
}
