#include "Weapons/Weapon.h"

Weapon::Weapon(sf::Sprite* _player, bool _person) :
    Cooldown(0.4f),
    player(_player),
    reloadTime(3.f),
    currentReloadTime(0.f),
    clipSize(12),
    currentClipSize(clipSize),
    damage(5.f),
    spread(6),
    iTexture(0),
    projectileSpeed(1.f),
    wAttackDistance(40.f),
    person(_person)
{
    //ctor
}

Weapon::Weapon(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize, float _damage, int _spread, bool _person) :
    Cooldown(_weaponCooldown),
    player(_player),
    reloadTime(_reloadTime),
    currentReloadTime(0.f),
    clipSize(_clipSize),
    currentClipSize(clipSize),
    damage(_damage),
    spread(_spread),
    iTexture(0),
    projectileSpeed(1.f),
    wAttackDistance(40.f),
    person(_person)
{

}

void Weapon::update()
{
    reduceCooldown();
    if(currentReloadTime >= 0.f)
        currentReloadTime -= frameTime;
}

bool Weapon::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <= 0.f && currentClipSize > 0)
    {
        currentClipSize--;
        currentCooldown = weaponCooldown;
        vecProjectiles.push_back(new Projectile(player, damage, spread, iTexture, projectileSpeed, person));
        return true;
    }
    if(currentClipSize <= 0)
    {
        currentReloadTime = reloadTime;
        currentClipSize = clipSize;
    }
    return false;
}

float Weapon::getReloadTime()
{
    return reloadTime;
}
float Weapon::getCurrentReloadTime()
{
    return currentReloadTime;
}

int Weapon::getClipSize()
{
    return clipSize;
}
int Weapon::getCurrentClipSize()
{
    return currentClipSize;
}
float Weapon::getAttackDistance()
{
    return wAttackDistance;
}
void Weapon::setITexture(int _iTexture)
{
    iTexture=_iTexture;
}
