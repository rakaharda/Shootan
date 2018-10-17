#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(float _damage) :
    damage(_damage), Cooldown(1.f)
{

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
    if(currentCooldown == 0.f)
    {
        currentCooldown = weaponCooldown;
        return damage;
    }
    return 0.f;
}
