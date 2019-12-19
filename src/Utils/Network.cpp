#include "Utils/Network.h"

Network::Network()
{

}

ConnectionModes Network::connectionMode = ConnectionModes::DEFAULT;
sf::TcpSocket Network::socket;

void Network::setConnection(ConnectionModes _mode, sf::IpAddress _ip)
{
    connectionMode = _mode;
    if(connectionMode == HOST)
    {
        sf::TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);
        sf::Packet packet;
        packet << "Connection complete";
        socket.send(packet);
    }
    else if(connectionMode == CLIENT)
    {
        socket.connect(_ip, 2000);
        sf::Packet packet;
        packet << "Connection complete";
        socket.send(packet);
    }
}

void Network::sendPacket(sf::Packet _packet)
{
    socket.send(_packet);
}

sf::Packet Network::receivePacket()
{
    sf::Packet packet;
    socket.receive(packet);
    return packet;
}

sf::IpAddress Network::getIp()
{
    return sf::IpAddress::getLocalAddress();
}
