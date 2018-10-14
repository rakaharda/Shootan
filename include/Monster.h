#ifndef MONSTER_H
#define MONSTER_H

#include "Enemy.h"

class Monster : public Enemy
{
    public:
        Monster(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints);
        virtual ~Monster();

    protected:

    private:
};

#endif // MONSTER_H
