#include "Utils/Network.h"

Network::Network(unsigned short _port)
{
    port = _port;
    if (socket.bind(port) != sf::Socket::Done)
    {
        std::cout << "Cannot bind port " << port << std::endl;
    }
}

Network::~Network()
{
    socket.unbind();
}
sf::Socket::Status Network::receive(sf::Packet& packet, sf::IpAddress &rcvAdr, unsigned short &rcvPort)
{
    sf::Socket::Status status = socket.receive(packet, rcvAdr, rcvPort);
    std::cout << "packet received from" << rcvAdr << ":" << rcvPort << std::endl;
    if(connections.find(rcvAdr) == connections.end() && status == sf::Socket::Done)
        connections.insert(std::make_pair(rcvAdr, rcvPort));
    return status;
}

sf::Socket::Status Network::receive(sf::Packet& packet)
{
    sf::IpAddress rcvAdr;
    unsigned short rcvPort;
    return this->receive(packet, rcvAdr, rcvPort);
}

unsigned short Network::send(sf::Packet packet)
{
    unsigned short packetsFailed = 0;
    for(auto& i : connections)
    {
        if(socket.send(packet, i.first, i.second) != sf::Socket::Done)
        {
            packetsFailed++;
            std::cout << "Failed to send packet to " << i.first << ":" << i.second << std::endl;
        }
        else
            std::cout << "packet sent to" << i.first << ":" << i.second << std::endl;
    }
    return packetsFailed;
}

sf::Socket::Status Network::send(sf::Packet packet, sf::IpAddress senderAdr, unsigned short senderPort)
{
    socket.send(packet, senderAdr, senderPort);
    std::cout << "packet sent to" << senderAdr << ":" << senderPort << std::endl;
}
