#include "Weapons/SniperRifle.h"

SniperRifle::SniperRifle(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown = 0.5f;
    clipSize = 7;
    currentClipSize = clipSize;
    spread = 1;
    damage = 110.f;
    projectileSpeed = 3.f;
    name = "sniper";
    reloadTime = 0.1f;
}
