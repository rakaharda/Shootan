#include "Game/GSMPHost.h"

GSMPHost::GSMPHost(VideoSettings *_videoSettings)
{
    //Setting up the connection
    connect();
    setupSettings(_videoSettings);
    sf::Packet readyPacket;
    client.receive(readyPacket);
    string msg;
    readyPacket >> msg;
    if(msg == "ready")
    {
        cout << "Starting game!";
    }
}

void GSMPHost::connect()
{
    unsigned port = 2000;
    cout << "Listenning port " << port << endl;
    if(listener.listen(port) != sf::Socket::Done)
    {
        cout << "Cannot listen port " << port << endl;
    }
    cout << "Waiting for user to connect." << endl;
    if(listener.accept(client) != sf::Socket::Done)
    {
        cout << "Cannot connect client!" << endl;
    }
    cout << "Client connected!" << endl;
}

void GSMPHost::setupSettings(VideoSettings *_videoSettings)
{
    fieldSize = sf::IntRect(0, 0, 2000, 2000);
    videoSettings = _videoSettings;
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
    playerClient = new PlayerClient;
}

GSMPHost::~GSMPHost()
{
    //dtor
}

GameStates GSMPHost::update()
{
    ClientEvents event;
    sf::Packet packet;
    client.receive(packet);
    packet >> event;
    playerClient->update(event);
    return GameStates::GS_GAMEMODE_MPHOST;
}

void GSMPHost::handleEvents(sf::Event _event)
{

}

void GSMPHost::draw()
{
    window.draw(*playerClient);
}
