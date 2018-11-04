#include "Weapons/Autorifle.h"

Autorifle::Autorifle(sf::Sprite* _player) : Weapon(_player, 0.05f, 2.f, 30, 5.f, 8)
{
    projectileSpeed = 1.1f;
}