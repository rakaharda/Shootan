#include "Components/ClientEvents.h"

sf::Packet& operator <<(sf::Packet& packet, const ClientEvents& event)
{
    return packet << event.keyDownW << event.keyDownS << event.keyDownA << event.keyDownD << event.keyDownR << event.keyDownLMB << event.mousePosition.x << event.mousePosition.y;
}

sf::Packet& operator >>(sf::Packet& packet, ClientEvents& event)
{
    return packet >> event.keyDownW >> event.keyDownS >> event.keyDownA >> event.keyDownD >> event.keyDownR >> event.keyDownLMB >> event.mousePosition.x << event.mousePosition.y;
}
