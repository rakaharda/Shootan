#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
class Shotgun: public Weapon
{
public:
    Shotgun(sf::Sprite* _source);
    virtual ~Shotgun() {};
    bool addProjectile();
};

extern ResourceManager      *resources;

#endif //SHOTGUN
