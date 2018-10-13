#include "ShotGun.h"

ShotGun::ShotGun(sf::Sprite* _player): Weapon(_player)
{
    weaponCooldown=1.0f;
    clipSize=5;
    currentClipSize=clipSize;
    damage=1;
}

ShotGun::~ShotGun()
{
    //dtor
}

bool ShotGun::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <=0.f && currentClipSize>0)
    {
        if(this->waveNamber%3==2)
        {
            currentClipSize--;
            weaponCooldown=1.f;
            waveNamber=0;
        }
        else
        {
            waveNamber++;
            weaponCooldown=((float)(rand()%30+10))/1000;
        }
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
