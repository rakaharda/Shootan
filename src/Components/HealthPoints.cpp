#include "Components/HealthPoints.h"

HealthPoints::HealthPoints() :
    healthPoints(100.f),
    currentHealthPoints(healthPoints)
{

}

HealthPoints::HealthPoints(float _healthPoints) :
    healthPoints(_healthPoints),
    currentHealthPoints(healthPoints)
{

}

HealthPoints::~HealthPoints()
{
    //dtor
}

float HealthPoints::getHealthPoints()
{
    return healthPoints;
}
float HealthPoints::getCurrentHealthPoints()
{
    return currentHealthPoints;
}
void HealthPoints::setCurrentHealthPoints(float _hp)
{
    currentHealthPoints=_hp;
}
void HealthPoints::setHealthPoints(float _hp)
{
    healthPoints=_hp;
}

void HealthPoints::increaseHealthPoints(float _hp)
{
    setHealthPoints(_hp);
    setCurrentHealthPoints(_hp);
}

void HealthPoints::takeDamage(float _damage)
{
    if(currentHealthPoints < _damage)
        currentHealthPoints = 0.f;
    else
        currentHealthPoints -= _damage;
}
