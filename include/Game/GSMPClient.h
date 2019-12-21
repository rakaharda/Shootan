#ifndef GSMPCLIENT_H
#define GSMPCLIENT_H

#include "Game/GSMPHost.h"

using namespace std;

class GSMPClient : public GSMPHost
{
    public:
        GSMPClient(VideoSettings *_videoSettings);
        virtual ~GSMPClient();

    protected:
        void connect();
    private:
        sf::TcpSocket host;
};

#endif // GSMPCLIENT_H
