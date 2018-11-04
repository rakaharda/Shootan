#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Components/GameObject.h"
#include "Player/Player.h"
#include "Creatures/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Weapons/Autorifle.h"
#include "Weapons/Shotgun.h"
#include "Weapons/Gun.h"
#include "Weapons/SniperRifle.h"
#include "Components/Collision.h"
#include "Game/VideoSettings.h"
#include "Game/GSSurvival.h"
#include "GUI/Menu.h"
#include "GUI/MainMenu.h"
#include "Utils/FPSCounter.h"
#include "Utils/ResourceManager.h"

using namespace std;

class Game : private Collision
{
public:
    Game();
    virtual ~Game();
    void play();
private:
    enum GameStates
    {
        GS_LOADING_SCREEN,
        GS_MAINMENU,
        GS_GAMEMODE_SURVIVAL
    } gameState;
    sf::Font        font;
    sf::Clock*      gameClock;
    FPSCounter      fpsCounter;
    MainMenu        *menu;
    VideoSettings   *videoSettings;
    GameState       *currentGameState;
    bool            isPlaying;
    void loadResources();
    void loadSettings();
    void handleEvents();
    void update();
    void draw();
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <Projectile*> vecProjectiles;
extern vector <Enemy*>      vecEnemies;
extern vector <Perk*>       vecPerks;
extern ResourceManager      *resources;
#endif // GAME_H

