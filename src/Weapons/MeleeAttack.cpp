#include "Weapons/MeleeAttack.h"

MeleeAttack::MeleeAttack(sf::Sprite* _source) : Weapon(_source)
{
    damage = 20.f;
    currentCooldown = 1.f;
    weaponCooldown = currentCooldown;
    wAttackDistance = 0;
}

float MeleeAttack::getDamage()
{
    return damage;
}

void MeleeAttack::setDamage(float _damage)
{
    damage = _damage;
}

float MeleeAttack::attack()
{
    if(currentCooldown <= 0.f)
    {
        currentCooldown = weaponCooldown;
        return damage;
    }
    return 0.f;
}
