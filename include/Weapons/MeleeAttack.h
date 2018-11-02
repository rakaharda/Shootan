#ifndef MELEEATTACK_H
#define MELEEATTACK_H

#include "Weapon.h"

class MeleeAttack : public Weapon
{
public:
    MeleeAttack(sf::Sprite* _player, bool _person=0);
    virtual ~MeleeAttack() {};
    float getDamage();
    void  setDamage(float _damage);
    float attack();
    bool  addProjectile()
    {
        return false;
    };
protected:
private:
};

#endif // MELEEATTACK_H
