#ifndef FINDWEAPON_H
#define FINDWEAPON_H

#include "Perks/Perk.h"
#include "Weapons/Weapon.h"

class FindWeapon : public Perk
{
public:
    void pickUp();
    FindWeapon(int _xPos, int _yPos, Weapon* _weapon);
    virtual ~FindWeapon(){};
    Weapon * weapon;
};

#endif // FINDWEAPON_H
