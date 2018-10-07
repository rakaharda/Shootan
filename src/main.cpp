#include "game.h"

sf::RenderWindow window;
Game* game;

int main()
{
    game = new Game;
    game->play();
    return 0;
}
