#include "Weapons/SniperRifle.h"

SniperRifle::SniperRifle(sf::Sprite* _player, ResourceManager *_resources,  bool _person) : Weapon(_player, _resources, _person)
{
    weaponCooldown = 1.2f;
    clipSize = 7;
    currentClipSize = clipSize;
    spread = 1;
    damage = 20.f;
    projectileSpeed = 1.7f;
}
