#ifndef GAME_H
#define GAME_H

#include <SFML\Window.hpp>
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Autorifle.h"
#include "Shotgun.h"
#include "Gun.h"
#include "SniperRifle.h"
#include "Collision.h"
#include "Perk.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Game : private Collision
{
    public:
        Game();
        virtual ~Game();
        void play();
    private:
        Player* player;
        sf::Font font;
        sf::Text info; //temporary
        sf::Clock* gameClock;
        bool isPlaying;
        bool fullscreen;
        bool verticalSync;
        sf::Vector2u resolution;
        void showStats();
        void loadResources();
        void loadSettings();
        void processEvents();
        void collectTrash();
        void checkProjectiles();
        void checkEnemies();
        void checkPerks();
        void update();
        void draw();
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector <sf::Texture> vecTextures;
extern vector <Projectile*> vecProjectiles;
extern vector <Enemy*> vecEnemies;
extern vector <Perk*> vecPerks;
#endif // GAME_H

