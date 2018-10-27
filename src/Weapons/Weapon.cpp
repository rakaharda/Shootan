#include "Weapons/Weapon.h"

Weapon::Weapon(sf::Sprite* _player, bool _person) :
player(_player),
Cooldown(0.4f),
reloadTime(3.f),
currentReloadTime(0.f),
clipSize(12),
currentClipSize(clipSize),
damage(5.f),
spread(6),
projectileType(Projectile::ptSprite),
skills(0),
projectileSpeed(1.f),
wDistanceAttack(40.f),
person(_person)
{
    //ctor
}

Weapon::Weapon(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize, float _damage, int _spread, Projectile::ProjectileType _projectileType, bool _person) :
player(_player),
Cooldown(_weaponCooldown),
reloadTime(_reloadTime),
currentReloadTime(0.f),
clipSize(_clipSize),
currentClipSize(clipSize),
damage(_damage),
spread(_spread),
projectileType(_projectileType),
skills(0),
projectileSpeed(1.f),
wDistanceAttack(40.f),
person(_person)
{

}

Weapon::~Weapon()
{
    //dtor
}

void Weapon::update()
{
    reduceCooldown();
    if(currentReloadTime>=0.f)
        currentReloadTime -= frameTime;
}

bool Weapon::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <=0.f && currentClipSize>0)
    {
        currentClipSize--;
        currentCooldown = weaponCooldown;
        vecProjectiles.push_back(new Projectile(player, damage, spread, skills,projectileSpeed, person));
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
float Weapon::getDistanceAttack()
{
    return wDistanceAttack;
}
