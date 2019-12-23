#include "Game/GSMPClient.h"

GSMPClient::GSMPClient(VideoSettings *_videoSettings, string _ip)
{
    //ctor
    ip = _ip;
    setupSettings(_videoSettings);
    healthBar = new HealthBar(playerClient);
    ammoBar = new AmmoBar(playerClient);
    //host.setBlocking(false);
    playerHost = new PlayerClient;
    playerHost->setOpponentTexture();
}

void GSMPClient::connect(string _ip)
{
    sf::SocketSelector selector;
    selector.add(host);
    cout << "Connecting to host" << endl;
    status = host.connect(_ip, 2000);
    if(status != sf::Socket::Done)
    {
        cout << "Couldn't connect to host!" << endl;
    }
    else
    {
        cout << "Succesfully connected to host!" << endl;
        host.setBlocking(true);
    }
    sf::Packet readyPacket;
    readyPacket << "ready";
    host.send(readyPacket);
}

GameStates GSMPClient::update()
{
    if(status != sf::Socket::Done)
    {
        connect(ip);
    }
    else
    {
        sf::Packet incomingPacket, outgoingPacket;
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
        host.send(outgoingPacket);
        host.receive(incomingPacket);
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
        checkObstacles();
        updateGlobal();
        checkProjectiles();
        updateListener();
        if(gg)
            rematch();
        return GameStates::GS_GAMEMODE_MPCLIENT;
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
    healthBar = new HealthBar(playerClient);
    ammoBar = new AmmoBar(playerClient);
    playerClient->setBorders(2000.f, 2000.f);
}

void GSMPClient::updateView()
{
    GSMPHost::updateView(playerClient);
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
    host.send(packet);
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
    window.draw(*playerClient);
    window.draw(*playerHost);
    window.setView(window.getDefaultView());
    window.draw(*healthBar);
    window.draw(*ammoBar);
}

