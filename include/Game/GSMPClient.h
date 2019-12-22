#ifndef GSMPCLIENT_H
#define GSMPCLIENT_H

#include "Game/GSMPHost.h"

using namespace std;

class GSMPClient : public GSMPHost
{
    public:
        GSMPClient(VideoSettings *_videoSettings);
        virtual ~GSMPClient();
        GameStates update();
        void draw();
    protected:
        void connect();
    private:
        sf::TcpSocket host;
        PlayerClient* playerHost;
        void drawClient();
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector<Projectile*> vecProjectiles;
extern vector<Perk*> vecPerks;
extern ResourceManager *resources;
extern AudioSettings *audioSettings;

#endif // GSMPCLIENT_H
