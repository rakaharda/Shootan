#ifndef GSMPHOST_H
#define GSMPHOST_H

#include "Game/Gamestate.h"
#include "Game/SurvivalStates.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "Player/PlayerClient.h"

using namespace std;

class GSMPHost : public GameState, public Collision
{
    public:
        GSMPHost(VideoSettings *_videoSettings);
        GSMPHost(){};
        ~GSMPHost();
        virtual GameStates update();
        virtual void draw();
        void handleEvents(sf::Event _event);
    protected:
        sf::Sprite background;
        sf::View view;
        sf::IntRect fieldSize;
        VideoSettings   *videoSettings;
        virtual void connect();
        virtual void setupSettings(VideoSettings *_videoSettings);
        void updateView(GameObject* obj);
        void loadResources();
        PlayerClient* playerClient;
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
