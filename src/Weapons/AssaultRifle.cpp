#include "Weapons/AssaultRifle.h"

AssaultRifle::AssaultRifle(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown =  0.05f;
    reloadTime = 1.5f;
    clipSize = 30;
    currentClipSize = clipSize;
    damage = 20.f;
    spread = 9;
    projectileSpeed = 1.1f;
    reloadSoundKey = "assaultrifle_reload";
    name = "auto";
}
