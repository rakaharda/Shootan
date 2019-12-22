#ifndef DEATHZONE_H
#define DEATHZONE_H

#include "Obstacles/Obstacles.h"

class DeathZone : public Obstacles
{
public:
    void smash(Player* &players);
    DeathZone(int _xPos, int _yPos);
    virtual ~DeathZone(){};
    void update(){};
    bool checkActive(){};
protected:
    float timecounter = 1.f;
    float timereload = 1.f;

};

#endif // DEATHZONE_H

