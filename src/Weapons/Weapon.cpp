#include "Weapons/Weapon.h"

Weapon::Weapon(sf::Sprite* _player) :
    Cooldown(0.4f),
    player(_player),
    reloadTime(3.f),
    currentReloadTime(0.f),
    clipSize(12),
    currentClipSize(clipSize),
    damage(5.f),
    spread(6),
    skill(0),
    projectileSpeed(1.f),
    wAttackDistance(40.f),
    textureKey("projectile_1")
{
    //ctor
}

Weapon::Weapon(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize, float _damage, int _spread) :
    Cooldown(_weaponCooldown),
    player(_player),
    reloadTime(_reloadTime),
    currentReloadTime(0.f),
    clipSize(_clipSize),
    currentClipSize(clipSize),
    damage(_damage),
    spread(_spread),
    skill(0),
    projectileSpeed(1.f),
    wAttackDistance(40.f),
    textureKey("projectile_1")
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
        vecProjectiles.push_back(new Projectile(player, damage, spread, resources->getTexture(textureKey), projectileSpeed, skill));
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
void Weapon::setSkill(int _skill)
{
    skill = _skill;
}
