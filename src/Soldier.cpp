#include "Soldier.h"
Soldier::Soldier(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints) :
Enemy(_xPos, _yPos, _sprite, _healthPoints, 0.f)
{

}

void Soldier::setWeapon(Weapon* _weapon)
{
    delete(weapon);
    weapon = _weapon;
    distanceAttack=weapon->getDistanceAttack();
}

void Soldier::update()
{

    calculateRotation();
    m_sprite.setRotation(currentAngle);
    if(checkDistance())
        move();
    reduceCooldown();
    weapon->addProjectile();
    weapon->update();
}
