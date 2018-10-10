#include "../include/Game.h"

sf::RenderWindow window;
float frameTime;
vector <sf::Texture> vecTextures;
vector <GameObject*> vecProjectiles;

int main()
{
    Game* game;
    game = new Game;
    game->play();
    return 0;
}
