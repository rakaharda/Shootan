#include "Game/GSMPClient.h"

GSMPClient::GSMPClient(VideoSettings *_videoSettings, string _ip)
{
    //ctor
    ip = _ip;
    setupSettings(_videoSettings);
    //host.setBlocking(false);
    playerHost = new PlayerClient;
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
        event.keyDownW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        event.keyDownS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        event.keyDownA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        event.keyDownD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
        event.keyDownR = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
        event.keyDownLMB = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        event.angle = playerClient->setOrientation();
        outgoingPacket << event;
        host.send(outgoingPacket);
        host.receive(incomingPacket);
        sf::Vector2f posClient, posHost;
        float angleHost;
        incomingPacket >> posClient.x >> posClient.y >> posHost.x >> posHost.y >> angleHost;
        bool keyDownLMB;
        incomingPacket >> keyDownLMB;
        playerClient->update(posClient, event.keyDownLMB);
        playerHost->update(posHost, keyDownLMB);
        playerHost->setOrientation(angleHost);
        for(unsigned int i = 0; i < vecProjectiles.size(); i++)
            vecProjectiles[i]->update();
        updateView(playerClient);
        return GameStates::GS_GAMEMODE_MPCLIENT;
    }
}

GSMPClient::~GSMPClient()
{
    //dtor
}


void GSMPClient::draw()
{
    window.setView(view);
    window.draw(background);
    for(unsigned int i = 0; i < vecProjectiles.size(); i++)
        window.draw(*vecProjectiles[i]);
    window.draw(*playerClient);
    window.draw(*playerHost);
}
