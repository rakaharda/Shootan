#include "Game/Game.h"
#include <iostream>
Game::Game() : isPlaying(true)
{
    loadSettings();
    //openMainMenu = new bool;
    openMainMenu = false;
    window.setFramerateLimit(200);
    if(fullscreen)
        window.create(sf::VideoMode(resolution.x, resolution.y), "Shootan", sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(resolution.x, resolution.y), "Shootan");
    if (verticalSync)
        window.setVerticalSyncEnabled(true);
    else
        window.setVerticalSyncEnabled(false);
    loadResources();
    info.setFont(font);
    info.setFillColor(sf::Color::Black);
}

Game::~Game()
{
    delete(gameClock);
    delete(player);
}

void Game::play()
{
    srand(clock());
    loadResources();
    player = new Player;
    Perk::player=player;
    player->setWeapon(new Gun(&player->m_sprite, 1));
    vecEnemies.push_back(new Enemy (500,500,&player->m_sprite, 100.f));
    vecEnemies[vecEnemies.size() - 1]->setWeapon(new Gun(&(vecEnemies[vecEnemies.size() - 1])->m_sprite));
    gameClock = new sf::Clock;
    cout << "Starting main game loop"<<endl;
    while (isPlaying)
    {
        frameTime = gameClock->restart().asSeconds();
        showStats();
        handleEvents();
        checkProjectiles();
        checkEnemies();
        checkPerks();
        update();
        collectTrash();
        draw();
    }
}

void Game::showStats()
{
    stringstream ss;
    if(player->getWeapon()->getCurrentReloadTime() > 0.f)
        ss << player->getWeapon()->getCurrentReloadTime() << '/' << player->getWeapon()->getReloadTime();
    else
        ss << player->getWeapon()->getCurrentClipSize() << '/' << player->getWeapon()->getClipSize();
    ss << endl <<"HP: "<< player->getCurrentHealthPoints();
    info.setString(ss.str());
}
void Game::handleEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(openMainMenu)
            menu->processEvents(event);
        else
            player->handleEvents(event);
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
                if(!openMainMenu)
                    menu = new MainMenu(&openMainMenu, &fullscreen, &verticalSync);
                else
                {
                    openMainMenu = false;
                }
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

void Game::checkProjectiles()
{
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        for(unsigned int j = 0; j < vecEnemies.size(); j++)
        {
            if(checkCollision(vecProjectiles[i], vecEnemies[j]))
                if(vecProjectiles[i]->person)
                {
                    vecEnemies[j]->takeDamage(vecProjectiles[i]->getDamage());
                    vecProjectiles.erase(vecProjectiles.begin() + i);
                }
            if(checkCollision(vecProjectiles[i], player))
                if(!(vecProjectiles[i]->person))
                {
                    player->takeDamage(vecProjectiles[i]->getDamage());
                    vecProjectiles.erase(vecProjectiles.begin() + i);
                }
        }
}

void Game::checkEnemies()
{
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
    {
        if(vecEnemies[i]->toDelete)
        {
            vecPerks.push_back(new Fire(vecEnemies[i]->m_sprite.getPosition().x,vecEnemies[i]->m_sprite.getPosition().y));
            vecEnemies.erase(vecEnemies.begin() + i);
            cout<<i<<" deleted"<<endl;
        }
    }
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
    {
        if(checkCollision(player, vecEnemies[i]))
        {
            player->takeDamage(vecEnemies[i]->attack());
        }
    }
}
void Game::checkPerks()
{
     for(unsigned int i=0; i < vecPerks.size(); i++)
    {
        if(checkCollision(player, vecPerks[i]))
        {
            vecPerks[i]->pickUp();
            vecPerks.erase(vecPerks.begin() + i);
            continue;
        }
        if(vecPerks[i]->checkActive())
        {
            vecPerks.erase(vecPerks.begin() + i);
        }
    }
}
void Game::collectTrash()
{
    for(unsigned int i = 0; i<vecProjectiles.size(); i++)
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
    if(openMainMenu)
        return;
    player->update();
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        vecEnemies[i]->update();
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        vecProjectiles[i]->update();
    for(unsigned int i=0; i<vecPerks.size(); i++)
        vecPerks[i]->update();
}
void Game::draw()
{
    window.clear(sf::Color(235, 235, 235));
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        window.draw(*vecEnemies[i]);
    for(unsigned int i=0; i<vecPerks.size(); i++)
        window.draw(*vecPerks[i]);
    window.draw(*player);
    window.draw(info);
    if(openMainMenu)
        window.draw(*menu);
    window.display();
}

void Game::loadResources()
{
    font.loadFromFile("./data/fonts/arial.ttf");
    vecTextures.push_back(sf::Texture());
    vecTextures[0].loadFromFile("./data/projectiles/1.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[1].loadFromFile("./data/projectiles/2.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[2].loadFromFile("./data/projectiles/3.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[3].loadFromFile("./data/projectiles/1B.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[4].loadFromFile("./data/projectiles/2B.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[5].loadFromFile("./data/projectiles/3B.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[6].loadFromFile("./data/enemies/default_enemy.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[7].loadFromFile("./data/enemies/default_monster_nest.png");
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
