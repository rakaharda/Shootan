#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
class ShotGun: public Weapon
{
    public:
        ShotGun(sf::Sprite* _player);
        virtual ~ShotGun();
        bool addProjectile();
        int waveNamber=0;
};

#endif //SHOTGUN
