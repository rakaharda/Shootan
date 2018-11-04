#ifndef SNIPERRIFLE_H
#define SNIPERRIFLE_H

#include "Weapon.h"
class SniperRifle: public Weapon
{
public:
    SniperRifle(sf::Sprite* _player, ResourceManager *_resources);
    virtual ~SniperRifle() {};
};

#endif //SNIPERRIFLE
