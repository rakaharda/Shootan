#include "Game/GSMPHost.h"

GSMPHost::GSMPHost(VideoSettings *_videoSettings)
{
    //Setting up the connection
    connect();
    setupSettings(_videoSettings);
    player = new Player;
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

void GSMPHost::updateView(GameObject* obj)
{
    view.setCenter(obj->getSprite().getPosition().x, obj->getSprite().getPosition().y);
    if(view.getCenter().x < window.getSize().x / 2)
        view.setCenter(window.getSize().x / 2, view.getCenter().y);
    else if(view.getCenter().x > fieldSize.width - (window.getSize().x / 2))
        view.setCenter(fieldSize.width - (window.getSize().x / 2), view.getCenter().y);
    if(view.getCenter().y < window.getSize().y / 2)
        view.setCenter(view.getCenter().x, window.getSize().y / 2);
    else if(view.getCenter().y > fieldSize.height - (window.getSize().y / 2))
        view.setCenter(view.getCenter().x, fieldSize.height - (window.getSize().y / 2));
}

GSMPHost::~GSMPHost()
{
    //dtor
}

GameStates GSMPHost::update()
{
    ClientEvents event;
    sf::Packet incomingPacket, outgoingPacket;
    client.receive(incomingPacket);
    incomingPacket >> event;
    playerClient->update(event);
    outgoingPacket << playerClient->getSpritePointer()->getPosition().x << playerClient->getSpritePointer()->getPosition().y;
    client.send(outgoingPacket);
    updateView(player);
    return GameStates::GS_GAMEMODE_MPHOST;
}

void GSMPHost::handleEvents(sf::Event _event)
{

}

void GSMPHost::draw()
{
    window.setView(view);
    window.draw(*playerClient);
}
