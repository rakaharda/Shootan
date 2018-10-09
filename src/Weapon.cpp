#include "Weapon.h"

Weapon::Weapon(sf::Sprite* _player) :
player(_player),
weaponCooldown(1.f),
currentCooldown(0.f),
damage(5.f),
spread(6),
projectileType(Projectile::ptSprite)
{
    //ctor
}

Weapon::Weapon(sf::Sprite* _player, float _weaponCooldown, float _damage, int _spread, Projectile::ProjectileType _projectileType) :
player(_player),
weaponCooldown(_weaponCooldown),
currentCooldown(0.f),
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
    if (currentCooldown>=0.f)
        currentCooldown -= frameTime;
}

bool Weapon::addProjectile()
{
    if (currentCooldown <= 0.f)
    {
        currentCooldown = weaponCooldown;
        vecProjectiles.push_back(new Projectile(player, damage, spread));
        return true;
    }
    return false;
}
