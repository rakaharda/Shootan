#include "Game/GSMPClient.h"

GSMPClient::GSMPClient(VideoSettings *_videoSettings, string _ip) : network(sf::Socket::AnyPort)
{
    //ctor
    ip = _ip;
    videoSettings = _videoSettings;
    state = MPS_MENU_CONNECTING;
    setupSettings(_videoSettings);
    healthBar = new HealthBar(playerClient);
    ammoBar = new AmmoBar(playerClient);
    gameState = GS_GAMEMODE_MPCLIENT;
    playerHost = new PlayerClient;
    playerHost->setOpponentTexture();
    playerClient->increaseHealthPoints(200.f);
    playerHost->setSpeedUp(200.f);
    playerClient->setSpeedUp(200.f);
}

void GSMPClient::connect(string _ip)
{
    sf::IpAddress address(_ip);
    cout << "Connecting to host" << endl;
    sf::Packet readyPacket;
    readyPacket << "ready";
    network.send(readyPacket, address, 2000);
    network.receive(readyPacket);
    network.socket.setBlocking(false);
    state = MPS_MENU_WAITING;
}

GameStates GSMPClient::update()
{
    sf::Packet outgoingPacket, incomingPacket;
    switch(state)
    {
    case MPS_MENU_CONNECTING:
        connect(ip);
        break;
    case MPS_START_GAME:
        //host.setBlocking(false);
        resources->getMusic("GXRCH - Race for Wind")->play();
        state = MPS_PLAY;
        return gameState;
        break;
    case MPS_REMATCH:
        rematchPauseTime -= frameTime;

        if(rematchPauseTime <= 0.f)
        {
            state = MPS_PLAY;
            tScore.setCharacterSize(40);
            auto bounds = tScore.getGlobalBounds();
            tScore.setOrigin(bounds.width / 2, bounds.height / 2);
            tScore.setPosition(window.getSize().x / 2, 50);
        }
        else if (rematchPauseTime < 1.5)
        {
            stringstream ss;
            ss << score.first << " : " << score.second;
            tScore.setString(ss.str());
        }
        return gameState;
    case MPS_PLAY:
        ClientEvents event;
        sf::Int8 disconnect = 0;
        sf::Int8 hostDisconnect = 0;
        event.keyDownW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        event.keyDownS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        event.keyDownA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        event.keyDownD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        event.keyDownR = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
        event.keyDownLMB = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        event.angle = playerClient->setOrientation();
        outgoingPacket << disconnect << event << playerClient->getCurrentHealthPoints();
        network.send(outgoingPacket);
        if(network.receive(incomingPacket) == sf::Socket::Done)
        {
            sf::Vector2f posClient, posHost;
            incomingPacket >> hostDisconnect;
            if(hostDisconnect)
                return GameStates::GS_MAINMENU;
            float angleHost;
            incomingPacket >> posClient.x >> posClient.y >> posHost.x >> posHost.y >> angleHost;
            bool keyDownLMB;
            incomingPacket >> keyDownLMB;
            int gg;
            incomingPacket >> gg;
            playerClient->update(posClient, event.keyDownLMB);
            playerHost->update(posHost, keyDownLMB);
            playerHost->setOrientation(angleHost);
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
        }
        checkObstacles();
        updateGlobal();
        checkProjectiles();
        updateListener();

        if(*survivalStates == SS_PAUSE_MENU)
        {
            if(pauseMenu->getGameState() == GS_MAINMENU)
            gameState = pauseMenu->getGameState();
        }
        return gameState;
    }
}

void GSMPClient::rematch()
{
    delete(playerHost);
    delete(playerClient);
    delete(healthBar);
    delete(ammoBar);
    vecProjectiles.clear();
    vecProjectiles.reserve(200);
    playerHost = new PlayerClient;
    playerClient = new PlayerClient;
    playerHost->setOpponentTexture();
    playerClient->increaseHealthPoints(200.f);
    healthBar = new HealthBar(playerClient);
    ammoBar = new AmmoBar(playerClient);
    playerClient->setBorders(2000.f, 2000.f);
    state = MPS_REMATCH;
    rematchPauseTime = 3.f;
    tScore.setCharacterSize(100);
    auto bounds = tScore.getGlobalBounds();
    tScore.setOrigin(bounds.width / 2, bounds.height / 2);
    tScore.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

void GSMPClient::updateView()
{
    GSMPHost::updateView(playerClient);
}

void GSMPClient::updateTime()
{
    if(currentTime <= 0.f)
    {
        currentTime = overloadTime;
        counterWeapon++;
        Weapon* wp1;
        Weapon* wp2;
        switch(counterWeapon%3)
        {
            case 0: wp1 = new Shotgun(playerClient->getSpritePointer()); wp2 = new Shotgun(playerClient->getSpritePointer()); break;
            case 1: wp1 = new SniperRifle(playerClient->getSpritePointer()); wp2 = new SniperRifle(playerClient->getSpritePointer()); break;
            case 2: wp1 = new AssaultRifle(playerClient->getSpritePointer()); wp2 = new AssaultRifle(playerClient->getSpritePointer()); break;
            default: wp1 = new Shotgun(playerClient->getSpritePointer()); wp2 = new Shotgun(playerClient->getSpritePointer()); break;
        }
        vecPerks.push_back(new FindWeapon(1000,200,wp1));
        vecPerks.push_back(new FindWeapon(1000,1800,wp2));
        vecPerks.push_back(new UpSpeed(200,200));
        vecPerks.push_back(new UpSpeed(1800,1800));
        vecPerks.push_back(new Medicine(1800,200));
        vecPerks.push_back(new Medicine(200,1800));
    }
    else
    {
        currentTime -= frameTime;
    }
    for(unsigned int i=0; i < vecPerks.size(); i++)
    {
        vecPerks[i]->update();
        if(checkCollision(playerHost, vecPerks[i]))
        {
            vecPerks[i]->pickUp(playerHost);
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

void GSMPClient::checkObstacles()
{
    for(unsigned int i = 0; i < vecObstacles.size(); i++)
    {
        for(unsigned int j = 0; j < vecProjectiles.size(); j++)
        {
            if(checkCollision(vecProjectiles[j], vecObstacles[i]) && !(vecObstacles[i]->passability))
            {
                vecProjectiles[j]->markToDelete();
                if(vecProjectiles[j]->toDelete())
                    vecProjectiles.erase(vecProjectiles.begin()+j);
            }
        }
        if (checkCollision(playerClient, vecObstacles[i]) && (vecObstacles[i]->passability))
        {
            vecObstacles[i]->smash(playerClient);
        }
    }

}

void GSMPClient::updateListener()
{
    sf::Listener::setPosition(playerClient->getSprite().getPosition().x, playerClient->getSprite().getPosition().y, 0.f);
}

GSMPClient::~GSMPClient()
{
    sf::Packet packet;
    packet << sf::Int8(1);
    network.send(packet);
    vecProjectiles.clear();
    delete(playerClient);
    delete(playerHost);
    resources->getMusic("GXRCH - Race for Wind")->stop();
}

void GSMPClient::checkProjectiles()
{
    for (unsigned int i = 0; i < vecProjectiles.size(); i++)
    {
        if (vecProjectiles[i]->getSource() != playerHost->getSpritePointer())
            if (checkCollision(vecProjectiles[i], playerHost))
            {
                playerHost->takeDamage(vecProjectiles[i]->getDamage());
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

void GSMPClient::draw()
{
    window.setView(view);
    window.draw(background);
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    for(unsigned int i = 0; i < vecObstacles.size(); i++)
        window.draw(*vecObstacles[i]);
    for (unsigned int i = 0; i < vecPerks.size(); i++)
        window.draw(*vecPerks[i]);
    window.draw(*playerClient);
    window.draw(*playerHost);
    window.setView(window.getDefaultView());
    window.draw(tScore);
    window.draw(*healthBar);
    window.draw(*ammoBar);
    if(*survivalStates == SS_PAUSE_MENU)
        window.draw(*pauseMenu);
}

