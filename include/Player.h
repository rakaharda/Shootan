#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "GameObject.h"
#include "Weapon.h"
#include "Autorifle.h"
#include "Shotgun.h"
#include "HealthPoints.h"

using namespace std;

class Player : public GameObject, public HealthPoints
{
    public:
        Player();
        virtual ~Player();
        void update();
        void processEvents(sf::Event event);
        Weapon* getWeapon();
        void setWeapon(Weapon* _weapon);
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
