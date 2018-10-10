#include "Weapon.h"

Weapon::Weapon(sf::Sprite* _player) :
player(_player),
weaponCooldown(0.4f),
currentCooldown(0.f),
reloadTime(3.f),
currentReloadTime(0.f),
clipSize(12),
currentClipSize(clipSize),
damage(5.f),
spread(6),
projectileType(Projectile::ptSprite)
{
    //ctor
}

Weapon::Weapon(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize, float _damage, int _spread, Projectile::ProjectileType _projectileType) :
player(_player),
weaponCooldown(_weaponCooldown),
currentCooldown(0.f),
reloadTime(_reloadTime),
currentReloadTime(0.f),
clipSize(_clipSize),
currentClipSize(clipSize),
damage(_damage),
spread(_spread),
projectileType(_projectileType)
{

}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::update()
{
    if(currentCooldown>=0.f)
        currentCooldown -= frameTime;
    if(currentReloadTime>=0.f)
        currentReloadTime -= frameTime;
}

bool Weapon::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <=0.f && currentClipSize>0)
    {
        currentClipSize--;
        currentCooldown = weaponCooldown;
        vecProjectiles.push_back(new Projectile(player, damage, spread));
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
float Weapon::getCooldown()
{
    return weaponCooldown;
}
float Weapon::getCurrentCooldown()
{
    return currentCooldown;
}
int Weapon::getClipSize()
{
    return clipSize;
}
int Weapon::getCurrentClipSize()
{
    return currentClipSize;
}