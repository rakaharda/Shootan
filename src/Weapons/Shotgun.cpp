#include "Weapons/Shotgun.h"

Shotgun::Shotgun(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown = 1.0f;
    clipSize = 5;
    currentClipSize = clipSize;
    damage = 10.f;
    spread = 7;
    projectileSpeed = 0.9f;
    waveCount = 0;
    shotSoundKey = "shotgun_shot";
    reloadSoundKey = "shotgun_reload";
}

bool Shotgun::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <= 0.f && (currentClipSize > 0 || waveCount != 0))
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
            vecProjectiles.push_back(new Projectile(source, damage, spread, resources->getTexture(textureKey), i, projectileSpeed, skill));
        if(waveCount == 1)
            playShotSound();
        return true;
    }
    if(currentClipSize <= 0)
    {
        playReloadSound();
        currentReloadTime = reloadTime;
        currentClipSize = clipSize;
    }
    return false;
}
