#ifndef GUN_H
#define GUN_H

#include "Weapon.h"
class Gun: public Weapon
{
public:
    Gun(sf::Sprite* _player, ResourceManager *_resources);
    virtual ~Gun(){};
    void setITexture(int _iTexture);
};

#endif //GUN
