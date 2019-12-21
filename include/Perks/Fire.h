#ifndef FIRE_H
#define FIRE_H

#include "Perks/Perk.h"
#include "Projectiles/Projectile.h"

class Fire : public Perk
{
public:
    void pickUp(Player* players = player);
    Fire(int _xPos, int _yPos);
    virtual ~Fire(){};
};
extern vector <Projectile*> vecProjectiles;
#endif // FIRE_H
