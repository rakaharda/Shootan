#include "Shotgun.h"

Shotgun::Shotgun(sf::Sprite* _player): Weapon(_player)
{
    weaponCooldown=1.0f;
    clipSize=5;
    currentClipSize=clipSize;
}

Shotgun::~Shotgun()
{
    //dtor
}

bool Shotgun::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <=0.f && currentClipSize>0)
    {
        currentClipSize--;
        currentCooldown = weaponCooldown;
        for(int i=0;i<5;i++)
        {
            vecProjectiles.push_back(new Projectile(player, damage, spread+((-2+i)*10)));
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
