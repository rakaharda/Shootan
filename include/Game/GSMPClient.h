#ifndef GSMPCLIENT_H
#define GSMPCLIENT_H

#include "Game/GSMPHost.h"

using namespace std;

class GSMPClient : public GSMPHost
{
    public:
        GSMPClient(VideoSettings *_videoSettings, string _ip);
        virtual ~GSMPClient();
        GameStates update();
        void draw();
    private:
        void checkProjectiles();
        void connect(string _ip);
        void updateView();
        void checkObstacles();
        void updateListener();
        void rematch();
        sf::TcpSocket host;
        PlayerClient* playerHost;
        string ip;
        void drawClient();
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector<Projectile*> vecProjectiles;
extern vector<Perk*> vecPerks;
extern ResourceManager *resources;
extern AudioSettings *audioSettings;

#endif // GSMPCLIENT_H
