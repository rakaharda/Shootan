#include "Game/Game.h"
#include "resources.h"

sf::RenderWindow     window;
float                frameTime;
ResourceManager      *resources;
vector <Projectile*> vecProjectiles;
vector <Perk*>       vecPerks;
AudioSettings        *audioSettings;

int main()
{
    Game* game;
    game = new Game;
    game->play();
    return 0;
}
