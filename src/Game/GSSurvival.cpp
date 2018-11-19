#include "Game/GSSurvival.h"

GSSurvival::GSSurvival(VideoSettings *_videoSettings) :
    player(new Player),
    fieldSize(sf::IntRect(0, 0, 3840, 2160)),
    videoSettings(_videoSettings),
    openPauseMenu(false),
    openPerkMenu(false)
{
    loadResources();
    perkMenu = new PerkMenu(&openPerkMenu, &player);
    pauseMenu = new PauseMenu(videoSettings,&openPauseMenu);
    background.setTexture(resources->getTexture("backgroundTile"));
    background.setTextureRect(fieldSize);
    info.setFont(resources->getFont("arial"));
    info.setFillColor(sf::Color::Red);
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
    player->setWeapon(new AssaultRifle(&player->m_sprite));
    healthBar = new HealthBar(player);
    vecEnemies.reserve(200);
    vecDestroyers.reserve(200);
    vecProjectiles.clear();
    vecProjectiles.reserve(200);
    vecPerks.clear();
    vecPerks.reserve(20);
    //!
    k = 0; //need to delete
    Perk::player = player;
    enemyFactory = new EnemyFactory(&player->m_sprite, fieldSize, &vecEnemies);
    resources->getMusic("GXRCH - HARD")->setLoop(true);
    resources->getMusic("GXRCH - HARD")->play();
}

GSSurvival::~GSSurvival()
{
    delete(player);
    delete(pauseMenu);
    delete(perkMenu);
}

GameStates GSSurvival::update()
{
    if(openPauseMenu||openPerkMenu)
        return pauseMenu->gameState;
    if(player->getCurrentHealthPoints() > 0.f)
    {
        player->update();
        enemyFactory->update();
        for(unsigned int i = 0; i < vecProjectiles.size(); i++)
            vecProjectiles[i]->update();
        for(unsigned int i=0; i<vecPerks.size(); i++)
            vecPerks[i]->update();
        for(unsigned int i=0; i<vecDestroyers.size(); i++)
            vecDestroyers[i].update();
        healthBar->update();
        updateView();
        updateListener();
        updateStats();
        checkProjectiles();
        checkMelee();
        checkPerks();
        checkDestroyers();
        collectTrash();
        updateView();
        draw();
    }
    return GameStates::GS_GAMEMODE_SURVIVAL;
}

void GSSurvival::updateStats()
{
    stringstream ss;
    ss<< endl << endl;
    if(player->getWeapon()->getCurrentReloadTime() > 0.f)
        ss << player->getWeapon()->getCurrentReloadTime() << '/' << player->getWeapon()->getReloadTime();
    else
        ss << player->getWeapon()->getCurrentClipSize() << '/' << player->getWeapon()->getClipSize();
    ss << endl << "HP: " << player->getCurrentHealthPoints();
    ss << endl << "Score: " << enemyFactory->getScore();
    info.setString(ss.str());
}

void GSSurvival::updateListener()
{
    sf::Listener::setPosition(player->m_sprite.getPosition().x, player->m_sprite.getPosition().y, 0.f);
}

void GSSurvival::handleEvents(sf::Event _event)
{
    if(openPauseMenu)
        pauseMenu->handleEvents(_event);
        else if(openPerkMenu)
                {
                    perkMenu->handleEvents(_event);
                    if(_event.type == sf::Event::KeyPressed)
                        if(_event.key.code == sf::Keyboard::L)
                        openPerkMenu = false;
                    return;
                }
                else
                    player->handleEvents(_event);
    if(_event.type == sf::Event::KeyPressed)
    {
        if(_event.key.code == sf::Keyboard::Escape)
            {
            if(!openPauseMenu)
                openPauseMenu = true;
            else
                openPauseMenu = false;
            }
        if(_event.key.code == sf::Keyboard::L && !openPauseMenu)
            if(!openPerkMenu)
                openPerkMenu = true;
    }
}

void GSSurvival::collectTrash()
{
    for(unsigned int i = 0; i<vecProjectiles.size(); i++)
    {
        if(vecProjectiles[i]->m_sprite.getPosition().x > fieldSize.width + 400
                || vecProjectiles[i]->m_sprite.getPosition().x < -400
                || vecProjectiles[i]->m_sprite.getPosition().y > fieldSize.height + 400
                || vecProjectiles[i]->m_sprite.getPosition().y < -400)
            vecProjectiles.erase(vecProjectiles.begin() + i);
    }
}

void GSSurvival::checkProjectiles()
{
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
    {
        for(unsigned int j = 0; j < vecEnemies.size(); j++)
        {
            if(vecProjectiles[i]->getSource() != &vecEnemies[j]->m_sprite)
                if(vecEnemies[j]->isAlive)
                    if(checkCollision(vecProjectiles[i], vecEnemies[j]))
                        {
                            vecEnemies[j]->takeDamage(vecProjectiles[i]->getDamage());
                            vecEnemies[j]->setSkill(vecProjectiles[i]->getSkill());
                            vecProjectiles[i]->toDelete = true;
                        }
        }
        if(vecProjectiles[i]->getSource() != &player->m_sprite)
            if(checkCollision(vecProjectiles[i], player))
                {
                    player->takeDamage(vecProjectiles[i]->getDamage());
                    vecProjectiles[i]->toDelete = true;
                }
        if(vecProjectiles[i]->toDelete)
            vecProjectiles.erase(vecProjectiles.begin()+i);
    }
}

void GSSurvival::checkMelee()
{
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
    {
        if(vecEnemies[i]->isAlive)
            if(checkCollision(player, vecEnemies[i]))
            {
                player->takeDamage(vecEnemies[i]->attack());
            }
    }
}

void GSSurvival::checkPerks()
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

void GSSurvival::checkDestroyers()
{
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        {
        if(!vecEnemies[i]->isAlive)
            if(!vecEnemies[i]->isBeingDestroyed)
            {
                vecDestroyers.push_back(EntityDestroyer(vecEnemies[i]));
                vecEnemies[i]->isBeingDestroyed = true;
            }
        }
    for(unsigned int i = 0; i < vecDestroyers.size(); i++)
        if(vecDestroyers[i].toDelete == true)
        {
            vecDestroyers.erase(vecDestroyers.begin() + i);
        }
}

void GSSurvival::updateView()
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

void GSSurvival::loadResources()
{
    //*Fonts
    resources->addFont("arial", "./data/fonts/arial.ttf");
    //*Textures
        //Background
    resources->addTexture("backgroundTile", "./data/background/tile1.png", true);
        //Projectiles
    resources->addTexture("projectile_1",   "./data/projectiles/projectile1_test.png");
    resources->addTexture("projectile_2",   "./data/projectiles/projectile2.png");
        //Enemies
    resources->addTexture("default_enemy",  "./data/enemies/default_enemy.png");
    resources->addTexture("enemy_melee",    "./data/enemies/enemy_melee.png");
    resources->addTexture("enemy_range",    "./data/enemies/enemy_range.png");
    resources->addTexture("destroyer_bar",  "./data/enemies/destroyer_bar.png", true);
        //Perks
    resources->addTexture("perk_cross",     "./data/perks/perk_cross.png");
    resources->addTexture("perk_speedup",   "./data/perks/perk_speedup.png");
        //GUI
    resources->addTexture("healthbar_frame","./data/GUI/healthbar_frame.png");
    resources->addTexture("healthbar_cells","./data/GUI/healthbar_cells.png");
    //*For button
    resources->addTexture("buttonLVL",    "./data/GUI/perkMenu/ilvl.png");
}

void GSSurvival::draw()
{
    //*View of the game board
    window.setView(view);
    window.draw(background);
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        window.draw(*vecEnemies[i]);
    for(unsigned int i = 0; i < vecDestroyers.size(); i++)
        window.draw(vecDestroyers[i]);
    for(unsigned int i=0; i<vecPerks.size(); i++)
        window.draw(*vecPerks[i]);
    window.draw(*player);
    //* UI
    window.setView(window.getDefaultView());
    window.draw(*healthBar);
    window.draw(info);
    if(openPauseMenu)
        window.draw(*pauseMenu);
    if(openPerkMenu)
        window.draw(*perkMenu);
}
