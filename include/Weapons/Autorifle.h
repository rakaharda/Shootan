#ifndef AUTORIFLE_H
#define AUTORIFLE_H

#include "Weapon.h"
class Autorifle: public Weapon
{
public:
    Autorifle(sf::Sprite* _player, ResourceManager *_resources);
    virtual ~Autorifle() {};
};

#endif //AUTORIFLE
