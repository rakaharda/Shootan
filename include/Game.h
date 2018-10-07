#ifndef GAME_H
#define GAME_H

#include <SFML\Window.hpp>
#include <vector>
#include "GameObject.h"
#include "Player.h"

using namespace std;

class Game
{
    public:
        Game();
        virtual ~Game();
        void play();
    private:
        bool isPlaying;
        void ProcessEvents();
};

#endif // GAME_H

extern sf::RenderWindow window;
extern Game* game;