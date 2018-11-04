#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
class Shotgun: public Weapon
{
public:
    Shotgun(sf::Sprite* _player, ResourceManager *_resources);
    virtual ~Shotgun() {};
    bool addProjectile();
    int waveCount;
};

#endif //SHOTGUN
