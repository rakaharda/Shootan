#ifndef GUN_H
#define GUN_H

#include "Weapon.h"
class Gun: public Weapon
{
public:
    Gun(sf::Sprite* _source);
    virtual ~Gun(){};
};

#endif //GUN
