#include "game.h"

sf::RenderWindow window;
float frameTime;

int main()
{
    Game* game;
    game = new Game;
    game->play();
    return 0;
}
