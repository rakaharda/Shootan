#ifndef MEDICINE_H
#define MEDICINE_H

#include "Perks/Perk.h"
#include "Player/Player.h"

class Medicine : public Perk
{
public:
    void pickUp();
    Medicine(int _xPos, int _yPos, Player **_player);
    virtual ~Medicine(){};
};

#endif // MEDICINE_H
