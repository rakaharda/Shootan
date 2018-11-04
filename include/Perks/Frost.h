#ifndef FROST_H
#define FROST_H

#include "Perks/Perk.h"

class Frost : public Perk
{
public:
    void pickUp();
    Frost(int _xPos, int _yPos);
    virtual ~Frost(){};
};

#endif // FROST_H
