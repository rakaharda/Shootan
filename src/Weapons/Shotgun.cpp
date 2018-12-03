#include "Weapons/Shotgun.h"

Shotgun::Shotgun(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown = 0.5f;
    clipSize = 5;
    currentClipSize = clipSize;
    damage = 50.f;
    spread = 1;
    projectileSpeed = 0.9f;
    name = "shotgun";
    reloadTime = 1.5f;
}

bool Shotgun::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <= 0.f && currentClipSize > 0 )
    {
        currentClipSize--;
        weaponCooldown = 1.f;
        currentCooldown = weaponCooldown;
        for(int i = 0; i < 8; i++)
        {
            vecProjectiles.push_back(new Projectile(source, damage, spread, resources->getTexture(textureKey), i, projectileSpeed, skill));
        }
        playShotSound();

        return true;
    }
    if(currentClipSize <= 0)
    {
        //playReloadSound();
        currentReloadTime = reloadTime;
        currentClipSize = clipSize;
    }
    return false;
}
