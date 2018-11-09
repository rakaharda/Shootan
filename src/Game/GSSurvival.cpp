#include "Game/GSSurvival.h"

GSSurvival::GSSurvival(VideoSettings *_videoSettings)
{
    videoSettings = _videoSettings;
    resources = new ResourceManager;
    openPauseMenu = false;
    loadResources();
    fieldSize = sf::IntRect(0, 0, 3840, 2160);
    background.setTexture(resources->getTexture("backgroundTile"));
    background.setTextureRect(fieldSize);
    info.setFont(resources->getFont("arial"));
    info.setFillColor(sf::Color::Red);
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
    player = new Player;
    player->setWeapon(new AssaultRifle(&player->m_sprite));
    //!
    k = 0; //need to delete
    Perk::player = player;
    enemyFactory = new EnemyFactory(&player->m_sprite, fieldSize, &vecEnemies);
    resources->getMusic("GXRCH - HARD")->setVolume(50.f);
    resources->getMusic("GXRCH - HARD")->setLoop(true);
    resources->getMusic("GXRCH - HARD")->play();
}

GSSurvival::~GSSurvival()
{
    delete(player);
}

void GSSurvival::update()
{
    if(openPauseMenu)
        return;
    if(player->getCurrentHealthPoints() > 0.f)
    {
    player->update();
    enemyFactory->update();
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        vecProjectiles[i]->update();
    for(unsigned int i=0; i<vecPerks.size(); i++)
        vecPerks[i]->update();
    updateView();
    updateListener();
    updateStats();
    checkProjectiles();
    checkMelee();
    checkPerks();
    collectTrash();
    updateView();
    draw();
    }
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
        else
            player->handleEvents(_event);
    if(_event.type == sf::Event::KeyPressed)
        if(_event.key.code == sf::Keyboard::Escape)
            {
            if(!openPauseMenu)
                pauseMenu = new PauseMenu(videoSettings,&openPauseMenu);
            else
                openPauseMenu = false;
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
            if(checkCollision(vecProjectiles[i], vecEnemies[j]))
                {
                    vecEnemies[j]->takeDamage(vecProjectiles[i]->getDamage());
                    vecEnemies[j]->setSkill(vecProjectiles[i]->getSkill());
                    vecProjectiles[i]->toDelete = true;
                }
        }
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
        if(checkCollision(player, vecEnemies[i]))
        {
            player->takeDamage(vecEnemies[i]->attack());
        }
    }
}

/*void GSSurvival::checkEnemies()
{
    for(unsigned int i = 0; i < vecEnemies.size(); i++)
    {
        if(vecEnemies[i]->toDelete)
        {
            //
            if(k)
                vecPerks.push_back(new Frost(vecEnemies[i]->m_sprite.getPosition().x,vecEnemies[i]->m_sprite.getPosition().y));
            else
                vecPerks.push_back(new Fire(vecEnemies[i]->m_sprite.getPosition().x,vecEnemies[i]->m_sprite.getPosition().y));
            k=1-k;
            k++; //fix this code
            //vecPerks.push_back(new FindWeapon(vecEnemies[i]->m_sprite.getPosition().x,vecEnemies[i]->m_sprite.getPosition().y,new Gun(&player->m_sprite, 1)));
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
}*/
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
    resources->addTexture("backgroundTile", "./data/background/tile1.png", true);
    resources->addFont("arial", "./data/fonts/arial.ttf");
    resources->addTexture("projectile_1", "./data/projectiles/projectile1_test.png");
    resources->addTexture("projectile_2", "./data/projectiles/projectile2.png");
    resources->addTexture("default_enemy", "./data/enemies/default_enemy.png");
    resources->addTexture("enemy_melee", "./data/enemies/enemy_melee.png");
    resources->addTexture("enemy_range", "./data/enemies/enemy_range.png");
    resources->addSoundBuffer("pistol_shot",         "./data/sounds/pistol_shot.wav");
    resources->addSoundBuffer("pistol_reload",       "./data/sounds/pistol_reload.wav");
    resources->addSoundBuffer("assaultrifle_shot",   "./data/sounds/assaultrifle_shot.wav");
    resources->addSoundBuffer("assaultrifle_reload", "./data/sounds/assaultrifle_reload.wav");
    resources->addSoundBuffer("sniperrifle_shot",    "./data/sounds/sniperrifle_shot.wav");
    resources->addSoundBuffer("shotgun_shot",        "./data/sounds/shotgun_shot.wav");
    resources->addSoundBuffer("shotgun_reload",  "./data/sounds/shotgun_reload.wav");
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
    for(unsigned int i=0; i<vecPerks.size(); i++)
        window.draw(*vecPerks[i]);
    window.draw(*player);
    //* UI
    window.setView(window.getDefaultView());
    window.draw(info);
    if(openPauseMenu)
        window.draw(*pauseMenu);
}
