#ifndef MEDICINE_H
#define MEDICINE_H

#include "Perks/Perk.h"

class Medicine : public Perk
{
public:
    void pickUp();
    Medicine(int _xPos, int _yPos);
    virtual ~Medicine(){};
};

#endif // MEDICINE_H
