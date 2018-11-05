#ifndef ASSAULTRIFLE_H
#define ASSAULTRIFLE_H

#include "Weapon.h"
class AssaultRifle: public Weapon
{
public:
    AssaultRifle(sf::Sprite* _source);
    virtual ~AssaultRifle() {};
};

#endif //ASSAULTRIFLE
