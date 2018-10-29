#ifndef GAME_H
#define GAME_H

#include <SFML\Window.hpp>
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
#include "Game/Settings.h"
#include "GUI/Menu.h"
#include "GUI/MainMenu.h"
#include "Utils/FPSCounter.h"

using namespace std;

//*Field size 3840x2160 (2 times FullHD)

class Game : private Collision
{
public:
    Game();
    virtual ~Game();
    void play();
private:
    Player*       player;
    sf::Sprite    background;
    sf::Font      font;
    sf::Text      info; //temporary
    sf::Clock*    gameClock;
    sf::IntRect   fieldSize;
    sf::Texture   backgroundTexture;
    sf::View      view;
    FPSCounter    fpsCounter;
    MainMenu      *menu;
    VideoSettings *videoSettings;
    bool          isPlaying;
    bool          openMainMenu;
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

