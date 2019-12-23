#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Components/GameObject.h"
#include "Components/GameStates.h"
#include "Player/Player.h"
#include "Creatures/Enemy.h"
#include "Projectiles/Projectile.h"
#include "Weapons/AssaultRifle.h"
#include "Weapons/Shotgun.h"
#include "Weapons/Gun.h"
#include "Weapons/SniperRifle.h"
#include "Components/Collision.h"
#include "Components/GameStates.h"
#include "Utils/VideoSettings.h"
#include "Game/GSSurvival.h"
#include "Game/GSMainMenu.h"
#include "Game/GSMPHost.h"
#include "Game/GSMPClient.h"
#include "GUI/PauseMenu.h"
#include "Utils/FPSCounter.h"
#include "Utils/ResourceManager.h"

using namespace std;

class Game
{
public:
    Game();
    virtual ~Game();
    void play();
private:
    GameStates      gameState;
    sf::Font        font;
    sf::Clock*      gameClock;
    FPSCounter      fpsCounter;
    PauseMenu        *pauseMenu;
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
extern vector <Perk*>       vecPerks;
extern ResourceManager      *resources;
extern AudioSettings        *audioSettings;
extern GSMPHost             *multiplayerState;
#endif // GAME_H

