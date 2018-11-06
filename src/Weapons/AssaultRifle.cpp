#include "Weapons/AssaultRifle.h"

AssaultRifle::AssaultRifle(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown =  0.05f;
    reloadTime = 3.f;
    clipSize = 30;
    currentClipSize = clipSize;
    damage = 20.f;
    spread = 9;
    projectileSpeed = 1.1f;
    shotSoundKey = "assaultrifle_shot";
    reloadSoundKey = "assaultrifle_reload";
}