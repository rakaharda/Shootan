#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "GameObject.h"
#include "Weapon.h"

using namespace std;

class Player : public GameObject
{
    public:
        Player();
        virtual ~Player();
        void update();
        void processEvents(sf::Event event);
    private:
        sf::Texture texture;
        float speed;
        void move();
        Weapon* weapon;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // PLAYER_H
