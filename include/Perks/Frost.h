#ifndef FROST_H
#define FROST_H

#include "Perks/Perk.h"
#include "Projectiles/Projectile.h"

class Frost : public Perk
{
public:
    void pickUp(Player* players = player);
    Frost(int _xPos, int _yPos);
    virtual ~Frost(){};
};
extern vector <Projectile*> vecProjectiles;
#endif // FROST_H
