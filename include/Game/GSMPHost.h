#ifndef GSMPHOST_H
#define GSMPHOST_H

#include "Game/Gamestate.h"
#include "Game/SurvivalStates.h"
#include "Game/MultiplayerStates.h"
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
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
        void setState(MultiplayerStates _state);
        MultiplayerStates getState();
        sf::Socket::Status getStatus();
    protected:
        sf::Socket::Status status;
        sf::Sprite background;
        sf::View view;
        sf::IntRect fieldSize;
        sf::Text tScore;
        HealthBar *healthBar;
        AmmoBar         *ammoBar;
        VideoSettings   *videoSettings;
        MultiplayerStates state;
        virtual void connect();
        virtual void setupSettings(VideoSettings *_videoSettings);
        virtual void checkObstacles();
        virtual void updateView();
        void updateView(GameObject* obj);
        void updateStats();
        void updateEntities();
        virtual void checkProjectiles();
        void updateGlobal();
        void collectTrash();
        void loadResources();
        PlayerClient* playerClient;
        vector<Obstacles*> vecObstacles;
        void updateBackground();
        virtual void updateListener();
        virtual void rematch();
        float           bgColorRed;
        float           bgColorGreen;
        float           bgColorBlue;
        float           colorAmplifier;
        char            redModifier;
        char            greenModifier;
        char            blueModifier;
        pair<int, int> score;
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
