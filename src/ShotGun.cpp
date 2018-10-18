#include "Shotgun.h"

Shotgun::Shotgun(sf::Sprite* _player): Weapon(_player)
{
    weaponCooldown=1.0f;
    clipSize=5;
    currentClipSize=clipSize;
    damage=1;
    spread=7;
    projectileSpeed=0.9f;
}

Shotgun::~Shotgun()
{
    //dtor
}

bool Shotgun::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <=0.f && currentClipSize>0)
    {
        if(this->waveNamber%4==3)
        {
            currentClipSize--;
            weaponCooldown=1.f;
            waveNamber=0;
        }
        else
        {
            waveNamber++;
            weaponCooldown=((float)(rand()%10+15))/1000;
        }
        currentCooldown = weaponCooldown;
        for(int i=0;i<4;i++)
        {
            vecProjectiles.push_back(new Projectile(player, damage, spread, skills, i, projectileSpeed));
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
