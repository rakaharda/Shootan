#ifndef MONSTER_H
#define MONSTER_H

#include "Enemy.h"

class Monster : public Enemy
{
    public:
        Monster(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints, float _meleeDamage);
        virtual ~Monster(){};

    protected:

    private:
};

extern vector <sf::Texture> vecTextures;

#endif // MONSTER_H
