#ifndef GAME_H
#define GAME_H

#include <SFML\Window.hpp>
#include <vector>
#include "Components/GameObject.h"
#include "Player/Player.h"
#include "Creatures/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Weapons/Autorifle.h"
#include "Weapons/Shotgun.h"
#include "Weapons/Gun.h"
#include "Weapons/SniperRifle.h"
#include "Components/Collision.h"
#include "GUI/Menu.h"
#include "GUI/MainMenu.h"
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
    Player*      player;
    sf::Font     font;
    sf::Text     info; //temporary
    sf::Clock*   gameClock;
    MainMenu     *menu;
    bool         isPlaying;
    bool         fullscreen;
    bool         verticalSync;
    sf::Vector2u resolution;
    bool         openMainMenu;
    void showStats();
    void loadResources();
    void loadSettings();
    void handleEvents();
    void collectTrash();
    void checkProjectiles();
    void checkEnemies();
    void update();
    void draw();
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <sf::Texture> vecTextures;
extern vector <Projectile*> vecProjectiles;
extern vector <Enemy*>      vecEnemies;
#endif // GAME_H

