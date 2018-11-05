#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
class Shotgun: public Weapon
{
public:
    Shotgun(sf::Sprite* _source);
    virtual ~Shotgun() {};
    bool addProjectile();
private:
    int waveCount;
};

extern ResourceManager      *resources;

#endif //SHOTGUN
