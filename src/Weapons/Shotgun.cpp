#include "Weapons/Shotgun.h"

Shotgun::Shotgun(sf::Sprite* _source) : Weapon(_source)
{
    weaponCooldown = 1.0f;
    clipSize = 5;
    currentClipSize = clipSize;
    damage = 10.f;
    spread = 1;
    projectileSpeed = 0.9f;
    shotSoundKey = "shotgun_shot";
    reloadSoundKey = "shotgun_reload";
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
            sounds.push_back(sf::Sound());
            sounds.back().setBuffer(resources->getSoundBuffer(shotSoundKey));
            sounds.back().setPosition(source->getPosition().x, source->getPosition().y, 0.f);
            sounds.back().setMinDistance(500);
            sounds.back().play();
        return true;
    }
    if(currentClipSize <= 0)
    {
        sounds.push_back(sf::Sound());
        sounds.back().setBuffer(resources->getSoundBuffer(reloadSoundKey));
        sounds.back().setPosition(source->getPosition().x, source->getPosition().y, 0.f);
        sounds.back().setMinDistance(50);
        sounds.back().play();
        currentReloadTime = reloadTime;
        currentClipSize = clipSize;
    }
    return false;
}
