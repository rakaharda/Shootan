#ifndef SNIPERRIFLE_H
#define SNIPERRIFLE_H

#include "Weapon.h"
class SniperRifle: public Weapon
{
public:
    SniperRifle(sf::Sprite* _source);
    virtual ~SniperRifle() {};
};

#endif //SNIPERRIFLE
