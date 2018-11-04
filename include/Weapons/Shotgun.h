#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
class Shotgun: public Weapon
{
public:
    Shotgun(sf::Sprite* _player, ResourceManager *_resources, bool _person = 0);
    virtual ~Shotgun() {};
    bool addProjectile();
    int waveCount;
};

#endif //SHOTGUN
