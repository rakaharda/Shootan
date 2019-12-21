#include "Game/GSMPClient.h"

GSMPClient::GSMPClient(VideoSettings *_videoSettings) : 
GSMPHost(_videoSettings)
{
    //ctor
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

GSMPClient::~GSMPClient()
{
    //dtor
}
