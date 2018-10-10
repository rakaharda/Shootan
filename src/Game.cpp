#include "Game.h"

Game::Game() : isPlaying(true)
{
    vector <sf::VideoMode> vMode = sf::VideoMode::getFullscreenModes();
    window.create(vMode[0], "Shootan", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    loadResources();
    font.loadFromFile("./data/fonts/arial.ttf");
    info.setFont(font);
    info.setFillColor(sf::Color::Black);
}

Game::~Game()
{
    //dtor
}

void Game::play()
{
    player = new Player;
    clock = new sf::Clock;
    while (isPlaying)
    {
        frameTime = clock->restart().asSeconds();
        stringstream ss;
        ss<<player->getWeapon()->getCurrentClipSize()<<'/'<<player->getWeapon()->getClipSize();
        info.setString(ss.str());
        processEvents();
        update();
        collectTrash();
        draw();
    }
}

void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::KeyPressed:
                if(event.key.code==sf::Keyboard::Escape)
                    {
                    window.close();
                    isPlaying = false;
                    return;
                    }
            default:
            player->processEvents(event);
                break;
            }
        }
}

void Game::collectTrash()
{
    for(unsigned int i=0; i<vecProjectiles.size(); i++)
        {
            if(vecProjectiles[i]->m_sprite.getPosition().x > window.getSize().x + 100
            || vecProjectiles[i]->m_sprite.getPosition().x < -100
            || vecProjectiles[i]->m_sprite.getPosition().y > window.getSize().y + 100
            || vecProjectiles[i]->m_sprite.getPosition().y < -100)
                vecProjectiles.erase(vecProjectiles.begin() + i);
        }
}
void Game::update()
{
    player->update();
    for(unsigned int i=0; i<vecProjectiles.size(); i++)
        vecProjectiles[i]->update();
}
void Game::draw()
{
    window.clear(sf::Color(235, 235, 235));
    for(unsigned int i=0; i<vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    window.draw(*player);
    window.draw(info);
    window.display();
}

void Game::loadResources()
{
    vecTextures.push_back(sf::Texture());
    vecTextures[0].loadFromFile("./data/projectiles/projectile1.png");
}