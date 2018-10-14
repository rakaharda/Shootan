#include "HealthPoints.h"

HealthPoints::HealthPoints()
{
    healthPoints = 100.f;
    currentHealthPoints = healthPoints;
}

HealthPoints::HealthPoints(float _healthPoints)
{
    healthPoints = _healthPoints;
    currentHealthPoints = healthPoints;
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
void HealthPoints::takeDamage(float _damage)
{
    if(currentHealthPoints < _damage)
        currentHealthPoints = 0.f;
    else 
        currentHealthPoints -= _damage;
}