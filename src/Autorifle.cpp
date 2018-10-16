#include "Autorifle.h"

Autorifle::Autorifle(sf::Sprite* _player): Weapon(_player)
{
    reloadTime=2.f;
    weaponCooldown=0.05f;
    clipSize=30;
    currentClipSize=clipSize;
    spread=8;
    projectileSpeed=1.1f;
}

Autorifle::~Autorifle()
{
    //dtor
}
