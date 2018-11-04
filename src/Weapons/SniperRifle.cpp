#include "Weapons/SniperRifle.h"

SniperRifle::SniperRifle(sf::Sprite* _player) : Weapon(_player)
{
    weaponCooldown = 1.2f;
    clipSize = 7;
    currentClipSize = clipSize;
    spread = 1;
    damage = 20.f;
    projectileSpeed = 1.7f;
}
