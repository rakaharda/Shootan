#include "Weapons/Gun.h"

Gun::Gun(sf::Sprite* _player, bool _person) : Weapon(_player, _person)
{
    weaponCooldown = 1.5f;
    clipSize = 10;
    currentClipSize = clipSize;
    spread = 9;
    damage = 25.f;
    projectileSpeed = 0.7f;
    iTexture = 3;
}