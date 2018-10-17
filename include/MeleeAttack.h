#ifndef MELEEATTACK_H
#define MELEEATTACK_H

#include "Cooldown.h"

class MeleeAttack : public Cooldown
{
public:
    MeleeAttack(float _damage);
    virtual ~MeleeAttack() {};
    float getDamage();
    void setDamage(float _damage);
    float attack();
protected:
    float damage;
private:
};

#endif // MELEEATTACK_H
