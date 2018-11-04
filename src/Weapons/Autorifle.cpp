#include "Weapons/Autorifle.h"

Autorifle::Autorifle(sf::Sprite* _player, ResourceManager *_resources, bool _person) : Weapon(_player, _resources, 0.05f, 2.f, 30, 5.f, 8, _person)
{
    projectileSpeed = 1.1f;
}