#ifndef SNIPERRIFLE_H
#define SNIPERRIFLE_H

#include "Weapon.h"
class SniperRifle: public Weapon
{
public:
    SniperRifle(sf::Sprite* _player, ResourceManager *_resources,  bool _person = 0);
    virtual ~SniperRifle() {};
};

#endif //SNIPERRIFLE
