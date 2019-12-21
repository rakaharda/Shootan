#include "Game/GSMPClient.h"

GSMPClient::GSMPClient(VideoSettings *_videoSettings)
{
    //ctor
    connect();
    setupSettings(_videoSettings);
    sf::Packet readyPacket;
    readyPacket << "ready";
    host.send(readyPacket);
}

void GSMPClient::connect()
{
    cout << "Connecting to host" << endl;
    sf::Socket::Status status = host.connect("192.168.1.91", 2000);
    if(status != sf::Socket::Done)
    {
        cout << "Couldn't connect to host!" << endl;
    }
    cout << "Succesfully connected to host!" << endl;
}

GameStates GSMPClient::update()
{
    sf::Packet packet;
    ClientEvents event;
    event.keyDownW = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    event.keyDownS = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    event.keyDownA = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    event.keyDownD = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    event.keyDownR = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    packet << event;
    host.send(packet);
    return GS_GAMEMODE_MPCLIENT;
}

GSMPClient::~GSMPClient()
{
    //dtor
}
