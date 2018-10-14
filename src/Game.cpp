#include "Game.h"
Game::Game() : isPlaying(true)
{
    loadSettings();
    if(fullscreen)
        window.create(sf::VideoMode(resolution.x, resolution.y), "Shootan", sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(resolution.x, resolution.y), "Shootan");
    if (verticalSync)
        window.setVerticalSyncEnabled(true);
    else
        window.setVerticalSyncEnabled(false);
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
    srand(clock());
    player = new Player;
    enemy = new Enemy (500,500,&player->m_sprite);
    gameClock = new sf::Clock;
    while (isPlaying)
    {
        frameTime = gameClock->restart().asSeconds();
        showAmmo();
        processEvents();
        update();
        collectTrash();
        draw();
    }
}

void Game::showAmmo()
{
    stringstream ss;
    if(player->getWeapon()->getCurrentReloadTime()>0.f)
        ss<<player->getWeapon()->getCurrentReloadTime()<<'/'<<player->getWeapon()->getReloadTime();
    else
        ss<<player->getWeapon()->getCurrentClipSize()<<'/'<<player->getWeapon()->getClipSize();
    info.setString(ss.str());
}
void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event))
        {
            switch(event.type)
            {
        case sf::Event::Closed:
                window.close();
                isPlaying = false;
                return;
            case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                case sf::Keyboard::Escape:
                    window.close();
                    isPlaying = false;
                    return;
                case sf::Keyboard::F12:
                    if(fullscreen)
                    {
                        window.close();
                        window.create(sf::VideoMode(resolution.x, resolution.y), "Shootan");
                        if (verticalSync)
                            window.setVerticalSyncEnabled(true);
                        fullscreen = false;
                    }
                    else
                    {
                        window.close();
                        window.create(sf::VideoMode(resolution.x, resolution.y), "Shootan", sf::Style::Fullscreen);
                        if (verticalSync)
                            window.setVerticalSyncEnabled(true);
                        fullscreen = true;
                    }
                    break;
                case sf::Keyboard::F11:
                    if (verticalSync)
                    {
                        window.setVerticalSyncEnabled(false);
                        verticalSync = false;
                    }
                    else
                    {
                        window.setVerticalSyncEnabled(true);
                        verticalSync = true;
                    }
                default:
                    break;
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
    enemy->update();
    for(unsigned int i=0; i<vecProjectiles.size(); i++)
        vecProjectiles[i]->update();
}
void Game::draw()
{
    window.clear(sf::Color(235, 235, 235));
    for(unsigned int i=0; i<vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    window.draw(*player);
    window.draw(*enemy);
    window.draw(info);
    window.display();
}

void Game::loadResources()
{
    vecTextures.push_back(sf::Texture());
    vecTextures[0].loadFromFile("./data/projectiles/projectile1.png");
}

void Game::loadSettings()
{
    FILE *fp = fopen("settings.conf", "r");
    unsigned int temp;
    fscanf(fp, "Fullscreen=%u\n", &temp);
    fullscreen = (bool)temp;
    fscanf(fp, "VerticalSync=%u\n", &temp);
    verticalSync = (bool)temp;
    fscanf(fp, "Width=%u\n", &(resolution.x));
    fscanf(fp, "Height=%u\n", &(resolution.y));
    if(resolution.x < 640)
        resolution.x = 640;
    if(resolution.y < 480)
        resolution.y = 480;
    fclose(fp);
}
