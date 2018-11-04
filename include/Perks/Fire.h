#ifndef FIRE_H
#define FIRE_H

#include "Perks/Perk.h"

class Fire : public Perk
{
public:
    void pickUp();
    Fire(int _xPos, int _yPos);
    virtual ~Fire(){};
};

#endif // FIRE_H
