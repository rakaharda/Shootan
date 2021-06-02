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
#include "GUI/PauseMenu.h"

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
        PauseMenu *pauseMenu;
        SurvivalStates* survivalStates;
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
        float overloadTime = 25.f;
        float currentTime = 0.f;
        int counterWeapon = 0;
        virtual void updateTime();
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
        GameStates      gameState;
        float           bgColorRed;
        float           bgColorGreen;
        float           bgColorBlue;
        float           colorAmplifier;
        char            redModifier;
        char            greenModifier;
        char            blueModifier;
        float           rematchPauseTime;
        bool            focus;
        pair<int, int>  score;
    private:
        unsigned short  port;
        sf::UdpSocket client;
        sf::IpAddress clientAddress;
        Player* player;
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector<Projectile*> vecProjectiles;
extern vector<Perk*> vecPerks;
extern ResourceManager *resources;
extern AudioSettings *audioSettings;
#endif // GSMPHOST_H
