#include "Game.h"

sf::RenderWindow window;
float frameTime;
vector <sf::Texture> vecTextures;
vector <Projectile*> vecProjectiles;
vector <Enemy*> vecEnemies;
int main()
{
    Game* game;
    game = new Game;
    game->play();
    return 0;
}
