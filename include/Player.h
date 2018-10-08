#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "GameObject.h"

using namespace std;

class Player : public GameObject
{
    public:
        Player();
        virtual ~Player();
        void ProcessEvents();
        void update();
    private:
        sf::Texture texture;
        void move(float speed);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // PLAYER_H
