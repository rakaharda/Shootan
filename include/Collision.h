#ifndef COLLISION_H
#define COLLISION_H

#include "GameObject.h"

class Collision
{
    public:
        Collision(){};
        virtual ~Collision(){};
        bool checkCollision(GameObject* _obj, GameObject* _obj2);
    protected:

    private:
};

#endif // COLLISION_H
