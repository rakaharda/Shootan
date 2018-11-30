#include "Weapons/Gun.h"

Gun::Gun(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown = 1.5f;
    clipSize = 10;
    currentClipSize = clipSize;
    spread = 9;
    damage = 25.f;
    projectileSpeed = 0.7f;
    textureKey = "projectile_2";
    name = "gun";
}

