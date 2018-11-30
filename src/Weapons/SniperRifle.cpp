#include "Weapons/SniperRifle.h"

SniperRifle::SniperRifle(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown = 1.2f;
    clipSize = 7;
    currentClipSize = clipSize;
    spread = 1;
    damage = 100.f;
    projectileSpeed = 1.7f;
    name = "sniper";
}
