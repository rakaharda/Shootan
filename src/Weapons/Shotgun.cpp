#include "Weapons/Shotgun.h"

Shotgun::Shotgun(sf::Sprite* _player, ResourceManager *_resources, bool _person) : Weapon(_player, _resources, _person)
{
    weaponCooldown = 1.0f;
    clipSize = 5;
    currentClipSize = clipSize;
    damage = 1.f;
    spread = 7;
    projectileSpeed = 0.9f;
    waveCount = 0;
}

bool Shotgun::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <= 0.f && currentClipSize > 0)
    {
        if(waveCount % 4 == 3)
        {
            currentClipSize--;
            weaponCooldown = 1.f;
            waveCount = 0;
        }
        else
        {
            waveCount++;
            weaponCooldown = ((float)(rand() % 10 + 15)) / 1000;
        }
        currentCooldown = weaponCooldown;
        for(int i = 0; i < 4; i++)
        {
            vecProjectiles.push_back(new Projectile(player, damage, spread, resources->getTexture(textureKey), i, projectileSpeed, person, skill));
        }
        return true;
    }
    if(currentClipSize <= 0)
    {
        currentReloadTime = reloadTime;
        currentClipSize = clipSize;
    }
    return false;
}
