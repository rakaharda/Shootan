#include "Game/GSSurvival.h"

GSSurvival::GSSurvival(VideoSettings *_videoSettings) :
    player(new Player),
    fieldSize(sf::IntRect(0, 0, 3840, 2160)),
    videoSettings(_videoSettings)
    //survivalState(SurvivalStates::SS_PLAY)
{
    loadResources();
    survivalState = new SurvivalStates;
    *survivalState = SurvivalStates::SS_PLAY;
    perkMenu = new PerkMenu(survivalState, &player);
    pauseMenu = new PauseMenu(videoSettings, survivalState);
    gameOverMenu = new GameOverMenu();
    background.setTexture(resources->getTexture("backgroundTile"));
    background.setTextureRect(fieldSize);
    background.setOrigin(fieldSize.width / 2, fieldSize.height / 2);
    background.setPosition(fieldSize.width / 2, fieldSize.height / 2);
    bgColorRed   = 255;
    bgColorGreen = 0;
    bgColorBlue  = 100;
    redModifier  = -1;
    greenModifier = 1;
    blueModifier = -1;
    colorAmplifier = 50.f;
    scaleAmplifier = 16.f;
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
    healthBar = new HealthBar(player);
    ammoBar = new AmmoBar(player);
    lvlBar = new LvlBar();
    vecEnemies.reserve(200);
    vecDestroyers.reserve(200);
    vecProjectiles.clear();
    vecProjectiles.reserve(200);
    vecPerks.clear();
    vecPerks.reserve(20);
    //!
    k = 0; //need to delete
    Perk::player = player;
    enemyFactory = new EnemyFactory(player, fieldSize, &vecEnemies);
    resources->getMusic("GXRCH - HARD")->setVolume(audioSettings->music);
    resources->getMusic("GXRCH - HARD")->setLoop(true);
    resources->getMusic("GXRCH - HARD(intro)")->setVolume(audioSettings->music);
    resources->getMusic("GXRCH - HARD(intro)")->play();
}

GSSurvival::~GSSurvival()
{
    delete(player);
    delete(pauseMenu);
    delete(perkMenu);
    resources->getMusic("GXRCH - HARD")->pause();
}

GameStates GSSurvival::update()
{
    if(player->getCurrentHealthPoints()<=0.f)
        *survivalState = SurvivalStates::SS_GAME_OVER;
    switch(*survivalState)
    {
    case SurvivalStates::SS_PLAY:
        updateStats();
        checkPerkMenu();
        updateBackground();
        updateEntities();
        updateFactories();
        updateMusic();
        updateView();
        updateListener();
        checkProjectiles();
        checkMelee();
        checkPerks();
        checkDestroyers();
        collectTrash();
        updateView();
        draw();
        return GameStates::GS_GAMEMODE_SURVIVAL;
    case SurvivalStates::SS_PAUSE_MENU:
        return pauseMenu->getGameState();
    case SurvivalStates::SS_PERK_MENU:
        return GameStates::GS_GAMEMODE_SURVIVAL;
    case SurvivalStates::SS_GAME_OVER:
        return gameOverMenu->getGameState();
    }
    return GameStates::GS_GAMEMODE_SURVIVAL;
}

void GSSurvival::updateBackground()
{
    sf::Color color;
    color.r = (int)bgColorRed;
    color.g = (int)bgColorGreen;
    color.b = (int)bgColorBlue;
    background.setColor(color);
    if(bgColorRed >= 255.f)
        redModifier = -1;
    if(bgColorGreen >= 255.f)
        greenModifier = -1;
    if(bgColorBlue >= 255.f)
        blueModifier = -1;
    if(bgColorRed <= 0.f)
        redModifier = 1;
    if(bgColorGreen <= 0.f)
        greenModifier = 1;
    if(bgColorBlue <= 0.f)
        blueModifier = 1;
    bgColorRed += (float)redModifier * frameTime * colorAmplifier;
    bgColorGreen += (float)greenModifier * frameTime * colorAmplifier;
    bgColorBlue += (float)blueModifier * frameTime * colorAmplifier;
}

void GSSurvival::updateEntities()
{
    player->update();
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        vecProjectiles[i]->update();
    for(unsigned int i=0; i<vecPerks.size(); i++)
        vecPerks[i]->update();
    for(unsigned int i=0; i<vecDestroyers.size(); i++)
        vecDestroyers[i].update();
}

void GSSurvival::updateFactories()
{
    enemyFactory->update();
}

void GSSurvival::updateMusic()
{
    if(resources->getMusic("GXRCH - HARD")->getStatus() != sf::Sound::Playing)
        if(resources->getMusic("GXRCH - HARD(intro)")->getStatus() == sf::Sound::Stopped)
            {
                colorAmplifier = 200.f;
                resources->getMusic("GXRCH - HARD")->play();
            }
}
void GSSurvival::updateStats()
{
    lvlBar->update(enemyFactory->getScore(),perkMenu->getnextlvl(),enemyFactory->getScore());
    healthBar->update();
    ammoBar->update();
}

void GSSurvival::updateListener()
{
    sf::Listener::setPosition(player->getSprite().getPosition().x, player->getSprite().getPosition().y, 0.f);
}

void GSSurvival::handleEvents(sf::Event _event)
{
    switch(*survivalState)
    {
    case SurvivalStates::SS_PLAY:
        player->handleEvents(_event);
        if(_event.type == sf::Event::KeyPressed)
            if(_event.key.code == sf::Keyboard::Escape)
                *survivalState = SurvivalStates::SS_PAUSE_MENU;
        break;
    case SurvivalStates::SS_PAUSE_MENU:
        pauseMenu->handleEvents(_event);
        if(_event.type == sf::Event::KeyPressed)
            if(_event.key.code == sf::Keyboard::Escape)
                *survivalState = SurvivalStates::SS_PLAY;
        break;
    case SurvivalStates::SS_PERK_MENU:
        perkMenu->handleEvents(_event);
        break;
    case SurvivalStates::SS_GAME_OVER:
        gameOverMenu->handleEvents(_event);
        break;
    default:
        break;
    }
}

void GSSurvival::collectTrash()
{
    for(unsigned int i = 0; i<vecProjectiles.size(); i++)
    {
        if(vecProjectiles[i]->getSprite().getPosition().x > fieldSize.width + 400
                || vecProjectiles[i]->getSprite().getPosition().x < -400
                || vecProjectiles[i]->getSprite().getPosition().y > fieldSize.height + 400
                || vecProjectiles[i]->getSprite().getPosition().y < -400)
            vecProjectiles.erase(vecProjectiles.begin() + i);
    }
}

void GSSurvival::checkProjectiles()
{
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
    {
        for(unsigned int j = 0; j < vecEnemies.size(); j++)
        {
            if(vecProjectiles[i]->getSource() != vecEnemies[j]->getSpritePointer())
                if(vecEnemies[j]->isAlive())
                    if(checkCollision(vecProjectiles[i], vecEnemies[j]))
                        {
                            vecEnemies[j]->takeDamage(vecProjectiles[i]->getDamage());
                            vecEnemies[j]->setSkill(vecProjectiles[i]->getSkill());
                            vecProjectiles[i]->markToDelete();
                        }
        }
        if(vecProjectiles[i]->getSource() != player->getSpritePointer())
            if(checkCollision(vecProjectiles[i], player))
                {
                    player->takeDamage(vecProjectiles[i]->getDamage());
                    vecProjectiles[i]->markToDelete();
                }
        if(vecProjectiles[i]->toDelete())
            vecProjectiles.erase(vecProjectiles.begin()+i);
    }
}

void GSSurvival::checkMelee()
{
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
    {
        if(vecEnemies[i]->isAlive())
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

void GSSurvival::checkPerkMenu()
{
        if(reloadAnimation <= 0.f)
        {
            perkMenu->updatelvl(enemyFactory->getScore());
            if(perkMenu->getlvl() && perkMenu->canOpen())
            {
                ianimation += 0.8f;
                    if(ianimation >= 5.f)
                    {
                        ianimation = 5.f;
                        offanimation = true;
                        *survivalState = SurvivalStates::SS_PERK_MENU;
                    }
            }
            if(offanimation)
            {
                ianimation -= 0.8f;
                if(ianimation <= 1.f)
                {
                    ianimation = 1.f;
                    offanimation = false;
                }
            }
            reloadAnimation = 0.2f;
        }
        else
            reloadAnimation -= frameTime;
        frameTime /= ianimation;
}

void GSSurvival::checkDestroyers()
{
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
        {
        if(!vecEnemies[i]->isAlive())
            if(!vecEnemies[i]->isBeingDestroyed())
            {
                vecDestroyers.push_back(EntityDestroyer(vecEnemies[i]));
                vecEnemies[i]->destroy();
                sounds.push_back(sf::Sound());
                sounds.back().setBuffer(resources->getSoundBuffer("destroy"));
                sounds.back().setVolume(audioSettings->sounds / 2.f);
                sounds.back().setPosition(vecEnemies[i]->getSprite().getPosition().x, vecEnemies[i]->getSprite().getPosition().y, 0.f);
                sounds.back().setMinDistance(500);
                sounds.back().play();
            }
        }
    for(unsigned int i = 0; i < vecDestroyers.size(); i++)
        if(vecDestroyers[i].toDelete())
        {
            vecDestroyers.erase(vecDestroyers.begin() + i);
        }
}

void GSSurvival::updateView()
{
    view.setCenter(player->getSprite().getPosition().x, player->getSprite().getPosition().y);
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
    resources->addTexture("perk_frost",     "./data/perks/Blue.png");
    resources->addTexture("perk_fire",      "./data/perks/Red.png");
    resources->addTexture("perk_weapon",    "./data/perks/perk_weapon.png");
        //GUI
    resources->addTexture("healthbar_frame",           "./data/GUI/gameInterface/healthbar_frame.png");
    resources->addTexture("healthbar_cells",           "./data/GUI/gameInterface/healthbar_cells.png");
    resources->addTexture("projectiles_scale_default", "./data/GUI/gameInterface/projectiles_scale_default.png");
    resources->addTexture("projectiles_scale_fire",    "./data/GUI/gameInterface/projectiles_scale_fire.png");
    resources->addTexture("projectiles_scale_freeze",  "./data/GUI/gameInterface/projectiles_scale_freeze.png");
    resources->addTexture("projectiles_scale_double",  "./data/GUI/gameInterface/projectiles_scale_double.png");
    resources->addTexture("projectiles_edge",          "./data/GUI/gameInterface/projectiles_edge.png");
    resources->addTexture("lvlbar_frame",              "./data/GUI/gameInterface/lvlbar_frame.png");
    resources->addTexture("lvlbar_cells",              "./data/GUI/gameInterface/lvlbar_cells.png");
    resources->addTexture("lvlbar_animation",          "./data/GUI/gameInterface/lvlbar_animation.png");
    resources->addTexture("lvlbar_lvlup",              "./data/GUI/gameInterface/lvlbar_lvlup.png");
    //*Numbers
    resources->addTexture("score_number_0", "./data/GUI/gameInterface/numbers/score_number_0.png");
    resources->addTexture("score_number_1", "./data/GUI/gameInterface/numbers/score_number_1.png");
    resources->addTexture("score_number_2", "./data/GUI/gameInterface/numbers/score_number_2.png");
    resources->addTexture("score_number_3", "./data/GUI/gameInterface/numbers/score_number_3.png");
    resources->addTexture("score_number_4", "./data/GUI/gameInterface/numbers/score_number_4.png");
    resources->addTexture("score_number_5", "./data/GUI/gameInterface/numbers/score_number_5.png");
    resources->addTexture("score_number_6", "./data/GUI/gameInterface/numbers/score_number_6.png");
    resources->addTexture("score_number_7", "./data/GUI/gameInterface/numbers/score_number_7.png");
    resources->addTexture("score_number_8", "./data/GUI/gameInterface/numbers/score_number_8.png");
    resources->addTexture("score_number_9", "./data/GUI/gameInterface/numbers/score_number_9.png");
    //*For button
    resources->addTexture("buttonLVL",      "./data/GUI/perkMenu/ilvl.png");
    resources->addTexture("mainBackground", "./data/GUI/MainMenu/mainBackground.png");
    //*Sound buffers
    resources->addSoundBuffer("laser1",  "./data/sounds/laser1.wav");
    resources->addSoundBuffer("destroy", "./data/sounds/destroy.wav");
    //*Music
    resources->addMusic("GXRCH - HARD", "./data/music/act.ogg");
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
    window.draw(*ammoBar);
    window.draw(*lvlBar);
    switch(*survivalState)
    {
    case SurvivalStates::SS_PAUSE_MENU:
        window.draw(*pauseMenu);
        break;
    case SurvivalStates::SS_PERK_MENU:
        window.draw(*perkMenu);
        break;
    case SurvivalStates::SS_GAME_OVER:
        window.draw(*gameOverMenu);
        break;
    default:
        break;
    }
}
