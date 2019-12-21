#ifndef GSMPHOST_H
#define GSMPHOST_H

#include "Game/Gamestate.h"
#include "Game/SurvivalStates.h"
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

class GSMPHost : public GameState, public Collision
{
    public:
        GSMPHost(VideoSettings *_videoSettings);
        ~GSMPHost();
        GameStates update();
        void draw();
        void handleEvents(sf::Event _event);
    protected:
        sf::View view;
        sf::IntRect fieldSize;
        VideoSettings   *videoSettings;
        virtual void connect();
    private:
        Player* player;
        sf::TcpListener listener;
        sf::TcpSocket client;
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector<Projectile*> vecProjectiles;
extern vector<Perk*> vecPerks;
extern ResourceManager *resources;
extern AudioSettings *audioSettings; 
#endif // GSMPHOST_H
