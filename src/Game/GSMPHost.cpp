#include "Game/GSMPHost.h"

GSMPHost::GSMPHost(VideoSettings *_videoSettings)
{

    //Setting up the connection
    status = sf::Socket::NotReady;
    state = MPS_MENU_CONNECTING;
    setupSettings(_videoSettings);
    player = new Player;
    player->setBorders(2000.f, 2000.f);
    player->setPosition(100.f, 1000.f);
    player->increaseHealthPoints(200.f);
    playerClient->setBorders(2000.f, 2000.f);
    playerClient->setPosition(1900, 1000);
    healthBar = new HealthBar(player);
    ammoBar = new AmmoBar(player);
    //client.setBlocking(false);
    listener.setBlocking(false);
    unsigned port = 2000;
    cout << "Listenning port " << port << endl;
    if (listener.listen(port) != sf::Socket::Done)
    {
        cout << "Cannot listen port " << port << endl;
    }
    player->setSpeedUp(200.f);
    playerClient->setSpeedUp(200.f);
}

void GSMPHost::connect()
{
    unsigned port = 2000;
    sf::SocketSelector selector;
    selector.add(listener);
    cout << "Waiting for user to connect." << endl;

        if(listener.accept(client) != sf::Socket::Done)
        {
            //cout << "Cannot connect client!" << endl;
        }
        else
        {
            //cout << "Client connected!" << endl;
            sf::Packet readyPacket;
           // client.setBlocking(false);
            client.receive(readyPacket);
            string msg;
            readyPacket >> msg;
            if(msg == "ready")
            {
                status = sf::Socket::Done;
                //client.setBlocking(true);
                listener.setBlocking(true);
                cout << "Starting game!";
                state = MPS_MENU_WAITING;
            }
        }
}

void GSMPHost::setupSettings(VideoSettings *_videoSettings)
{
    fieldSize = sf::IntRect(0, 0, 2000, 2000);
    videoSettings = _videoSettings;
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
    loadResources();
    background.setTexture(resources->getTexture("backgroundTile"));
    background.setTextureRect(fieldSize);
    background.setOrigin(fieldSize.width / 2, fieldSize.height / 2);
    background.setPosition(fieldSize.width / 2, fieldSize.height / 2);
    playerClient = new PlayerClient;
    playerClient->setBorders(2000.f, 2000.f);
    tScore.setString("0 : 0");
    tScore.setCharacterSize(40);
    tScore.setFillColor(sf::Color(180, 120, 255));
    tScore.setFont(resources->getFont("Mylodon-Light"));
    auto bounds = tScore.getGlobalBounds();
    tScore.setOrigin(bounds.width / 2, bounds.height / 2);
    tScore.setPosition(window.getSize().x / 2 ,  50);
    vecObstacles.reserve(20);
    vecObstacles.push_back(new Wall(200, 670, 0));
    vecObstacles.push_back(new Wall(200, 1330, 0));
    vecObstacles.push_back(new Wall(1800, 670, 0));
    vecObstacles.push_back(new Wall(1800, 1330, 0));
    vecObstacles.push_back(new Wall(500, 400, 2));
    vecObstacles.push_back(new Wall(500, 1600, 2));
    vecObstacles.push_back(new Wall(1500, 400, 2));
    vecObstacles.push_back(new Wall(1500, 1600, 2));
    vecObstacles.push_back(new Wall(1000, 1000, 2));
    vecProjectiles.clear();
    vecProjectiles.reserve(200);
    bgColorRed   = 255;
    bgColorGreen = 0;
    bgColorBlue  = 100;
    redModifier  = -1;
    greenModifier = 1;
    blueModifier = -1;
    colorAmplifier = 50.f;
    resources->getMusic("GXRCH - Race for Wind")->setVolume(audioSettings->music);
    resources->getMusic("GXRCH - Race for Wind")->setLoop(true);
}

void GSMPHost::updateBackground()
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

sf::Socket::Status GSMPHost::getStatus()
{
    return status;
}

void GSMPHost::updateView()
{
    updateView(player);
}

void GSMPHost::updateView(GameObject *obj)
{
    view.setCenter(obj->getSprite().getPosition().x, obj->getSprite().getPosition().y);
    if (view.getCenter().x < window.getSize().x / 2)
        view.setCenter(window.getSize().x / 2, view.getCenter().y);
    else if (view.getCenter().x > fieldSize.width - (window.getSize().x / 2))
        view.setCenter(fieldSize.width - (window.getSize().x / 2), view.getCenter().y);
    if (view.getCenter().y < window.getSize().y / 2)
        view.setCenter(view.getCenter().x, window.getSize().y / 2);
    else if (view.getCenter().y > fieldSize.height - (window.getSize().y / 2))
        view.setCenter(view.getCenter().x, fieldSize.height - (window.getSize().y / 2));
}

GSMPHost::~GSMPHost()
{
    resources->getMusic("GXRCH - Race for Wind")->stop();
    sf::Packet packet;
    packet << sf::Int8(1);
    client.send(packet);
    //dtor
}

GameStates GSMPHost::update()
{
    sf::Packet outgoingPacket, incomingPacket;
    switch(state)
    {
    case MPS_MENU_CONNECTING:
        connect();
        break;
    case MPS_START_GAME:
        resources->getMusic("GXRCH - Race for Wind")->play();
        state = MPS_PLAY;
        break;
    case MPS_PLAY:
        ClientEvents event;
        float clientHealth;
        sf::Int8 disconnect = 0;
        sf::Int8 clientDisconnect = 0;
        int gg = 0;
        sf::Packet incomingPacket, outgoingPacket;
        client.receive(incomingPacket);
        incomingPacket >> clientDisconnect;
        if(clientDisconnect)
            return GameStates::GS_MAINMENU;
        incomingPacket >> event >> clientHealth;
        playerClient->update(event);
        playerClient->setOrientation(event.angle);
        player->update();
        checkObstacles();
        if(clientHealth <= 0.f || player->getCurrentHealthPoints() <= 0.f)
        {
            if(clientHealth <= 0.f && player->getCurrentHealthPoints() <= 0.f)
                gg = 3;
            else if(clientHealth <= 0.f)
                gg = 2;
            else
                gg = 1;
        }
        outgoingPacket << disconnect << playerClient->getSpritePointer()->getPosition().x << playerClient->getSpritePointer()->getPosition().y <<
                          player->getSpritePointer()->getPosition().x << player->getSpritePointer()->getPosition().y <<
                          player->getSpritePointer()->getRotation() << sf::Mouse::isButtonPressed(sf::Mouse::Left) << gg;
        client.send(outgoingPacket);
        updateGlobal();
        checkProjectiles();
        updateListener();
        if(gg)
        {
            if(gg == 3)
            {
                score.first++;
                score.second++;
            } else if(gg == 2)
                score.first++;
            else
                score.second++;
            rematch();
        }
        return GameStates::GS_GAMEMODE_MPHOST;
    }
}

void GSMPHost::setState(MultiplayerStates _state)
{
    state = _state;
}

MultiplayerStates GSMPHost::getState()
{
    return state;
}

void GSMPHost::rematch()
{
    delete(player);
    delete(playerClient);
    delete(healthBar);
    delete(ammoBar);
    vecProjectiles.clear();
    vecProjectiles.reserve(200);
    player = new Player;
    playerClient = new PlayerClient;
    healthBar = new HealthBar(player);
    ammoBar = new AmmoBar(player);
    player->setBorders(2000.f, 2000.f);
    player->setPosition(100.f, 1000.f);
    player->increaseHealthPoints(200.f);
    playerClient->setBorders(2000.f, 2000.f);
    playerClient->setPosition(1900, 1000);
    playerClient->setOpponentTexture();
}

void GSMPHost::updateGlobal()
{
    updateStats();
    updateEntities();
    updateBackground();
    updateTime();
    collectTrash();
    updateView();
    stringstream ss;
    ss << score.first << " : " << score.second;
    tScore.setString(ss.str());
}

void GSMPHost::updateTime()
{
    if(currentTime <= 0.f)
    {
        currentTime = overloadTime;
        counterWeapon++;
        Weapon* wp1;
        Weapon* wp2;
        switch(counterWeapon%3)
        {
            case 0: wp1 = new Shotgun(player->getSpritePointer()); wp2 = new Shotgun(player->getSpritePointer()); break;
            case 1: wp1 = new SniperRifle(player->getSpritePointer()); wp2 = new SniperRifle(player->getSpritePointer()); break;
            case 2: wp1 = new AssaultRifle(player->getSpritePointer()); wp2 = new AssaultRifle(player->getSpritePointer()); break;
            default: wp1 = new Shotgun(player->getSpritePointer()); wp2 = new Shotgun(player->getSpritePointer()); break;
        }
        vecPerks.push_back(new FindWeapon(100,100,wp1));
        vecPerks.push_back(new FindWeapon(1900,1900,wp2));
        vecPerks.push_back(new UpSpeed(200,100));
        vecPerks.push_back(new UpSpeed(1800,1900));
        vecPerks.push_back(new Medicine(300,100));
        vecPerks.push_back(new Medicine(1700,1900));
    }
    else
    {
        currentTime -= frameTime;
    }
    for(unsigned int i=0; i < vecPerks.size(); i++)
    {
        vecPerks[i]->update();
        if(checkCollision(player, vecPerks[i]))
        {
            vecPerks[i]->pickUp(player);
            vecPerks.erase(vecPerks.begin() + i);
            continue;
        }
        if(checkCollision(playerClient, vecPerks[i]))
        {
            vecPerks[i]->pickUp(playerClient);
            vecPerks.erase(vecPerks.begin() + i);
            continue;
        }
        if(vecPerks[i]->checkActive())
        {
            vecPerks.erase(vecPerks.begin() + i);
        }
    }
}

void GSMPHost::checkProjectiles()
{
    for (unsigned int i = 0; i < vecProjectiles.size(); i++)
    {
        if (vecProjectiles[i]->getSource() != player->getSpritePointer())
            if (checkCollision(vecProjectiles[i], player))
            {
                player->takeDamage(vecProjectiles[i]->getDamage());
                vecProjectiles[i]->markToDelete();
            }
        if (vecProjectiles[i]->getSource() != playerClient->getSpritePointer())
            if (checkCollision(vecProjectiles[i], playerClient))
            {
                playerClient->takeDamage(vecProjectiles[i]->getDamage());
                vecProjectiles[i]->markToDelete();
            }
        if (vecProjectiles[i]->toDelete())
            vecProjectiles.erase(vecProjectiles.begin() + i);
    }
}

void GSMPHost::collectTrash()
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

void GSMPHost::updateListener()
{
    sf::Listener::setPosition(player->getSprite().getPosition().x, player->getSprite().getPosition().y, 0.f);
}

void GSMPHost::updateEntities()
{
    for (unsigned int i = 0; i < vecProjectiles.size(); i++)
        vecProjectiles[i]->update();
    for (unsigned int i = 0; i < vecPerks.size(); i++)
        vecPerks[i]->update();
}

void GSMPHost::updateStats()
{
    healthBar->update();
    ammoBar->update();
}

void GSMPHost::handleEvents(sf::Event _event)
{
}

void GSMPHost::loadResources()
{
    //*Fonts
    resources->addFont("arial", "./data/fonts/arial.ttf");
    //*Textures
    //Background
    resources->addTexture("backgroundTile", "./data/background/tile1.png", true);
    //Obstacles
    resources->addTexture("obstacles_wall", "./data/Obstacles/Wall.png");
    resources->addTexture("obstacles_death_zone", "./data/Obstacles/Death_zone.png");
    //Projectiles
    resources->addTexture("projectile_1", "./data/projectiles/projectile1_test.png");
    resources->addTexture("projectile_2", "./data/projectiles/projectile2.png");
    //Enemies
    resources->addTexture("default_enemy", "./data/enemies/default_enemy.png");
    resources->addTexture("enemy_melee", "./data/enemies/enemy_melee.png");
    resources->addTexture("enemy_range", "./data/enemies/enemy_range.png");
    resources->addTexture("destroyer_bar", "./data/enemies/destroyer_bar.png", true);
    //Perks
    resources->addTexture("perk_cross", "./data/perks/perk_cross.png");
    resources->addTexture("perk_speedup", "./data/perks/perk_speedup.png");
    resources->addTexture("perk_frost", "./data/perks/Blue.png");
    resources->addTexture("perk_fire", "./data/perks/Red.png");
    resources->addTexture("perk_weapon", "./data/perks/perk_weapon.png");
    //GUI
    resources->addTexture("healthbar_frame", "./data/GUI/gameInterface/healthbar_frame.png");
    resources->addTexture("healthbar_cells", "./data/GUI/gameInterface/healthbar_cells.png");
    resources->addTexture("projectiles_scale_default", "./data/GUI/gameInterface/projectiles_scale_default.png");
    resources->addTexture("projectiles_scale_fire", "./data/GUI/gameInterface/projectiles_scale_fire.png");
    resources->addTexture("projectiles_scale_freeze", "./data/GUI/gameInterface/projectiles_scale_freeze.png");
    resources->addTexture("projectiles_scale_double", "./data/GUI/gameInterface/projectiles_scale_double.png");
    resources->addTexture("projectiles_edge", "./data/GUI/gameInterface/projectiles_edge.png");
    resources->addTexture("lvlbar_frame", "./data/GUI/gameInterface/lvlbar_frame.png");
    resources->addTexture("lvlbar_cells", "./data/GUI/gameInterface/lvlbar_cells.png");
    resources->addTexture("lvlbar_animation", "./data/GUI/gameInterface/lvlbar_animation.png");
    resources->addTexture("lvlbar_lvlup", "./data/GUI/gameInterface/lvlbar_lvlup.png");
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
    resources->addTexture("buttonLVL", "./data/GUI/perkMenu/ilvl.png");
    resources->addTexture("mainBackground", "./data/GUI/MainMenu/mainBackground.png");
    resources->addFont("Mylodon-Light",               "./data/fonts/Mylodon-Light.otf");
    //*Sound buffers
    resources->addSoundBuffer("laser1", "./data/sounds/laser1.wav");
    resources->addSoundBuffer("destroy", "./data/sounds/destroy.wav");
    //*Music
    resources->addMusic("GXRCH - HARD", "./data/music/act.ogg");
    resources->addMusic("GXRCH - Race for Wind", "./data/music/mpmusic.wav");
}
void GSMPHost::checkObstacles()
{
    for (unsigned int i = 0; i < vecObstacles.size(); i++)
    {
        if (checkCollision(player, vecObstacles[i]))
        {
            vecObstacles[i]->smash(player);
        }
        if (checkCollision(playerClient, vecObstacles[i]) && !(vecObstacles[i]->passability))
        {
            vecObstacles[i]->smash(playerClient);
        }
        for (unsigned int j = 0; j < vecProjectiles.size(); j++)
        {
            if (checkCollision(vecProjectiles[j], vecObstacles[i]) && !(vecObstacles[i]->passability))
            {
                vecProjectiles[j]->markToDelete();
                if (vecProjectiles[j]->toDelete())
                    vecProjectiles.erase(vecProjectiles.begin() + j);
            }
        }
    }
}

void GSMPHost::draw()
{
    window.setView(view);
    window.draw(background);
    for (unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for (unsigned int i = 0; i < vecObstacles.size(); i++)
        window.draw(*vecObstacles[i]);
    for (unsigned int i = 0; i < vecPerks.size(); i++)
        window.draw(*vecPerks[i]);
    window.draw(*playerClient);
    window.draw(*player);
    window.setView(window.getDefaultView());
    window.draw(tScore);
    window.draw(*healthBar);
    window.draw(*ammoBar);
}
