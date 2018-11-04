#include "Weapons/Gun.h"

Gun::Gun(sf::Sprite* _player, ResourceManager *_resources, bool _person) : Weapon(_player, _resources, _person)
{
    weaponCooldown = 1.5f;
    clipSize = 10;
    currentClipSize = clipSize;
    spread = 9;
    damage = 25.f;
    projectileSpeed = 0.7f;
    skill = 4;
    textureKey = "projectile_1B";
}

void Gun::setITexture(int _iTexture)
{
    skill = _iTexture+4;
}
