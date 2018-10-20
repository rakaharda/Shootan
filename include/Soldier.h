#ifndef SOLDIER_H
#define SOLDIER_H

#include "Enemy.h"

class Soldier: public Enemy
{
    public:
        Soldier(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints);
        virtual ~Soldier(){};
        void update();
        void setWeapon(Weapon* _weapon);
    protected:

    private:
};

#endif // SOLDIER_H
