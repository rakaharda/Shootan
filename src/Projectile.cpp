#include "Projectile.h"

Projectile::Projectile(const sf::Sprite* _sprite, float _damage, int _spread) : 
damage(_damage),
speed(1000.f)
{
    m_sprite.setTexture(vecTextures[0]);
    m_sprite.setPosition(_sprite->getPosition());
    angle = ((rand() % _spread - _spread / 2) + _sprite->getRotation()) / 180 * M_PI;
}

Projectile::Projectile(const sf::Sprite* _sprite, float _damage, int _spread, float _speed) :
damage(_damage),
speed(_speed)
{
    m_sprite.setTexture(vecTextures[0]);
    m_sprite.setPosition(_sprite->getPosition());
    angle = ((rand() % _spread - _spread / 2) + _sprite->getRotation()) / 180 * M_PI;
}
Projectile::~Projectile()
{
    //dtor
}

void Projectile::update()
{
    m_sprite.move(cos(angle) * 1000.f * frameTime, sin(angle) * 1000.f * frameTime);
}

float Projectile::getDamage()
{
    return damage;
}
void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
