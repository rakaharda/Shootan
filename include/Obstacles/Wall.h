#ifndef WALL_H
#define WALL_H

#include "Obstacles/Obstacles.h"
#include "Components/Collision.h"



class Wall : public Obstacles, public Collision
{
public:
    void smash(Player* &players);
    void smash(PlayerClient* &players);
    Wall(int _xPos, int _yPos, int rot = 0);
    virtual ~Wall(){};
    void update(){};
    bool checkActive(){return 0;};
};

#endif // WALL_H
