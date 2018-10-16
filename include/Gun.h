#ifndef GUN_H
#define GUN_H

#include "Weapon.h"
class Gun: public Weapon
{
    public:
        Gun(sf::Sprite* _player);
        virtual ~Gun();
};

#endif //GUN
