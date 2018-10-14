#include "Autorifle.h"

Autorifle::Autorifle(sf::Sprite* _player): Weapon(_player, 0.2f, 3.f, 30, 5.f, 8, Projectile::ptSprite)
{

}

Autorifle::~Autorifle()
{
    //dtor
}
