#include "Game/GSMPHost.h"

GSMPHost::GSMPHost(VideoSettings *_videoSettings) : 
fieldSize(sf::IntRect(0, 0, 2000, 2000)),
videoSettings(_videoSettings)
{
    //Setting up the connection
    connect();
    view.setSize(videoSettings->width, videoSettings->height);
    view.setCenter(fieldSize.width / 2, fieldSize.height / 2);
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

GSMPHost::~GSMPHost()
{
    //dtor
}

GameStates GSMPHost::update()
{

    return GameStates::GS_GAMEMODE_SURVIVAL;
}

void GSMPHost::handleEvents(sf::Event _event)
{

}

void GSMPHost::draw()
{

}