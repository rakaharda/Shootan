#include "Autorifle.h"

Autorifle::Autorifle(sf::Sprite* _player): Weapon(_player)
{
    weaponCooldown=0.2f;
    clipSize=30;
    currentClipSize=clipSize;
    spread=8;
}

Autorifle::~Autorifle()
{
    //dtor
}
