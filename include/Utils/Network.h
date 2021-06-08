#ifndef NETWORK_H
#define NETWORK_H

#include <SFML/Network.hpp>
#include <unordered_map>
#include <iostream>
#include <thread>
#include <mutex>

class Network
{
public:
    Network(unsigned short _port = 2000);
    ~Network();
    sf::Socket::Status receive(sf::Packet& packet);
    sf::Socket::Status receive(sf::Packet& packet, sf::IpAddress &rcvAdr, unsigned short &rcvPort);
    unsigned short send(sf::Packet packet); // returns amount of packets failed to send
    sf::Socket::Status send(sf::Packet packet, sf::IpAddress senderAdr, unsigned short senderPort);
    sf::UdpSocket socket;
    void startPacketFiltering();
    void stopPacketFiltering();
    virtual void packetFiltering();
protected:
    std::map <sf::IpAddress, unsigned short> connections; //  <address, port>
    unsigned short port;
    bool filterPackets;
    sf::Packet lastPacket;
    sf::IpAddress lastReceiver;
    sf::Socket::Status lastStatus;
    unsigned short lastPort;
    std::mutex _lock;
};

#endif //NETWORK_H
