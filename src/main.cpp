#include "Game/Game.h"

sf::RenderWindow window;
float frameTime;
ResourceManager *resources;
vector <Projectile*> vecProjectiles;
vector <Enemy*> vecEnemies;
vector <Perk*> vecPerks;
int main()
{
    Game* game;
    game = new Game;
    game->play();
    return 0;
}
