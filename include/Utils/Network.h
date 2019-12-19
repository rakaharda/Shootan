#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>
#include "Utils/ConnectionModes.h"

class Network
{
public:
    Network();
    static sf::IpAddress getIp();
    static sf::Packet receivePacket();
    static void setConnection(ConnectionModes _mode, sf::IpAddress _ip);
    static void sendPacket(sf::Packet _packet);
private:
    static ConnectionModes connectionMode;
    static sf::TcpSocket socket;
};

#endif //NETWORK_H
