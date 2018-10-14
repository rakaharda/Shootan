#include "Monster.h"

Monster::Monster(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints) :
Enemy(_xPos, _yPos, _sprite, _healthPoints)
{
    //ctor
}

Monster::~Monster()
{
    //dtor
}
