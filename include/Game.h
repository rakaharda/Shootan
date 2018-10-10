#ifndef GAME_H
#define GAME_H

#include <SFML\Window.hpp>
#include <vector>
#include "GameObject.h"
#include "Player.h"
#include <sstream>
using namespace std;

class Game
{
    public:
        Game();
        virtual ~Game();
        void play();
    private:
        Player* player;
        sf::Font font;
        sf::Text info; //temporary
        sf::Clock* clock;
        bool isPlaying;
        void loadResources();
        void processEvents();
        void collectTrash();
        void update();
        void draw();
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector <sf::Texture> vecTextures;
extern vector <GameObject*> vecProjectiles;

#endif // GAME_H

