#include "Utils/Network.h"

Network::Network(unsigned short _port)
{
    port = _port;
    if (socket.bind(port) != sf::Socket::Done)
    {
        std::cout << "Cannot bind port " << port << std::endl;
    }
    filterPackets = false;
    receiveCall = false;
}

Network::~Network()
{
    socket.unbind();
}

sf::Socket::Status Network::receive(sf::Packet& packet, sf::IpAddress &rcvAdr, unsigned short &rcvPort)
{
    if(filterPackets == true)
    {
        receiveCall = true;
        _lock.lock();
        packet = lastPacket;
        rcvAdr = lastReceiver;
        rcvPort = lastPort;
        return lastStatus;
        _lock.unlock();
        receiveCall = false;
    }
    else
    {
        sf::Socket::Status status = socket.receive(packet, rcvAdr, rcvPort);
        if(connections.find(rcvAdr) == connections.end() && status == sf::Socket::Done)
            connections.insert(std::make_pair(rcvAdr, rcvPort));
        return status;
    }
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
    }
    return packetsFailed;
}

sf::Socket::Status Network::send(sf::Packet packet, sf::IpAddress senderAdr, unsigned short senderPort)
{
    return socket.send(packet, senderAdr, senderPort);
}

void Network::startPacketFiltering()
{
    filterPackets = true;
    socket.setBlocking(false);
    filteringThread = std::thread(Network::packetFiltering, this);
}

void Network::stopPacketFiltering()
{
    filterPackets = false;
}

void Network::packetFiltering()
{
    while(filterPackets)
    {
        if(!receiveCall)
        {
            _lock.lock();
            std::cout << "thread receiving packet" << std::endl;
            sf::Packet tempPacket;
            sf::IpAddress tempReceiver;
            unsigned short tempPort;
            if (socket.receive(tempPacket, tempReceiver, tempPort) == sf::Socket::Done)
            {
                lastPacket = tempPacket;
                lastReceiver = tempReceiver;
                lastPort = tempPort;
                lastStatus = sf::Socket::Done;
            }
            _lock.unlock();
        }
    }
}
