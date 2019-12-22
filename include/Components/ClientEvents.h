#ifndef CLIENTEVENTS_H
#define CLIENTEVENTS_H

#include <SFML/Network.hpp>

struct ClientEvents
{
    sf::Int8 keyDownW;
    sf::Int8 keyDownS;
    sf::Int8 keyDownA;
    sf::Int8 keyDownD;
    sf::Int8 keyDownR;
    sf::Int8 keyDownLMB;
    float    angle;
    ClientEvents()
    {
        keyDownW = 0;
        keyDownS = 0;
        keyDownA = 0;
        keyDownD = 0;
        keyDownR = 0;
        keyDownLMB = 0;
        angle = -1.f;
    }
};

sf::Packet& operator <<(sf::Packet& packet, const ClientEvents& event);

sf::Packet& operator >>(sf::Packet& packet, ClientEvents& event);

#endif
