#include "Game/Game.h"
#include <iostream>
Game::Game() : isPlaying(true)
{
    //Loading settings
    videoSettings = new VideoSettings;
    loadSettings();
    //Setting up window
    if(videoSettings->fullscreen)
        window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan", sf::Style::Fullscreen);
    else
        window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan");
    if (videoSettings->vsync)
        window.setVerticalSyncEnabled(true);
    else
        window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(videoSettings->framerateLimit);
    openMainMenu = false;
    loadResources();
    fieldSize = sf::IntRect(0, 0, 3840, 2160);
    background.setTexture(backgroundTexture);
    background.setTextureRect(fieldSize);
    info.setFont(font);
    info.setFillColor(sf::Color::Black);
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
}

Game::~Game()
{
    delete(gameClock);
    delete(player);
    delete(videoSettings);
}

void Game::play()
{
    srand(clock());
    loadResources();
    player = new Player;
    player->setWeapon(new SniperRifle(&player->m_sprite, 1));
    vecEnemies.push_back(new Enemy(500, 500, &player->m_sprite, 100.f));
    vecEnemies.push_back(new Enemy(0, 0, &player->m_sprite, 50.f));
    vecEnemies[0]->setWeapon(new Gun(&(vecEnemies[0])->m_sprite));
    vecEnemies[1]->setWeapon(new Gun(&(vecEnemies[1])->m_sprite));
    gameClock = new sf::Clock;
    cout << "Starting main game loop"<<endl;
    while (isPlaying)
    {
        frameTime = gameClock->restart().asSeconds();
        showStats();
        handleEvents();
        checkProjectiles();
        checkEnemies();
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
                    menu = new MainMenu(&openMainMenu, &videoSettings->fullscreen, &videoSettings->vsync);
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
    {
        for(unsigned int j = 0; j < vecEnemies.size(); j++)
        {
            if(checkCollision(vecProjectiles[i], vecEnemies[j]))
                if(vecProjectiles[i]->person)
                {
                    vecEnemies[j]->takeDamage(vecProjectiles[i]->getDamage());
                    vecProjectiles.erase(vecProjectiles.begin() + i);
                }
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
void Game::collectTrash()
{
    for(unsigned int i = 0; i<vecProjectiles.size(); i++)
    {
        if(vecProjectiles[i]->m_sprite.getPosition().x > fieldSize.width + 200
                || vecProjectiles[i]->m_sprite.getPosition().x < -200
                || vecProjectiles[i]->m_sprite.getPosition().y > fieldSize.height + 200
                || vecProjectiles[i]->m_sprite.getPosition().y < -200)
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
    fpsCounter.update();
    updateView();
}

void Game::updateView()
{
    view.setCenter(player->m_sprite.getPosition().x, player->m_sprite.getPosition().y);
    if(view.getCenter().x < window.getSize().x / 2)
        view.setCenter(window.getSize().x / 2, view.getCenter().y);
    else if(view.getCenter().x > fieldSize.width - (window.getSize().x / 2))
        view.setCenter(fieldSize.width - (window.getSize().x / 2), view.getCenter().y);
    if(view.getCenter().y < window.getSize().y / 2)
        view.setCenter(view.getCenter().x, window.getSize().y / 2);
    else if(view.getCenter().y > fieldSize.height - (window.getSize().y / 2))
        view.setCenter(view.getCenter().x, fieldSize.height - (window.getSize().y / 2));
}
void Game::draw()
{
    window.clear();
    //*View of the game board
    window.setView(view);
    window.draw(background);
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        window.draw(*vecEnemies[i]);
    window.draw(*player);
    //* UI
    window.setView(window.getDefaultView());
    window.draw(info);
    window.draw(fpsCounter);
    if(openMainMenu)
        window.draw(*menu);
    window.display();
}

void Game::loadResources()
{
    font.loadFromFile("./data/fonts/arial.ttf");
    vecTextures.push_back(sf::Texture());
    vecTextures[0].loadFromFile("./data/projectiles/projectile1.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[1].loadFromFile("./data/enemies/default_enemy.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[2].loadFromFile("./data/enemies/default_monster_nest.png");
    vecTextures.push_back(sf::Texture());
    vecTextures[3].loadFromFile("./data/projectiles/projectile2.png");
    backgroundTexture.loadFromFile("./data/background/tile1.png");
    backgroundTexture.setRepeated(true);
}

void Game::loadSettings()
{
    FILE *fp = fopen("settings.conf", "r");
    unsigned int temp;
    fscanf(fp, "Fullscreen=%u\n", &temp);
    videoSettings->fullscreen = (bool)temp;
    fscanf(fp, "VerticalSync=%u\n", &temp);
    videoSettings->vsync = (bool)temp;
    fscanf(fp, "Width=%u\n", &videoSettings->width);
    fscanf(fp, "Height=%u\n", &videoSettings->height);
    if(videoSettings->width < 640)
        videoSettings->width = 640;
    if(videoSettings->height < 480)
        videoSettings->height = 480;
    fclose(fp);
    videoSettings->framerateLimit = 200;
}
