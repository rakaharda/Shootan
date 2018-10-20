#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
class Shotgun: public Weapon
{
    public:
        Shotgun(sf::Sprite* _player, bool _person=0);
        virtual ~Shotgun();
        bool addProjectile();
        int waveNamber=0;
};

#endif //SHOTGUN
