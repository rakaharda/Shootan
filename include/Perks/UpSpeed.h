#ifndef UPSPEED_H
#define UPSPEED_H

#include "Perks/Perk.h"

class UpSpeed : public Perk
{
public:
    void pickUp();
    UpSpeed(int _xPos, int _yPos);
    virtual ~UpSpeed(){};
};

#endif // UPSPEED_H
