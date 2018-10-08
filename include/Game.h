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
        sf::Clock* clock;
    private:
        bool isPlaying;
        void ProcessEvents();
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // GAME_H

