#include "Projectiles/Projectile.h"

Projectile::Projectile(const sf::Sprite* _sprite, float _damage, int _spread, int _iTexture, float _speed, bool _person) :
    person(_person),
    damage(_damage),
    speed(_speed)
{
    speed=_speed;
    srand(time(NULL));
    m_sprite.setTexture(vecTextures[_iTexture]);
    m_sprite.setPosition(_sprite->getPosition());
    angle = ((rand() % _spread - _spread / 2) + _sprite->getRotation()) / 180 * M_PI;
}
Projectile::Projectile(const sf::Sprite* _sprite, float _damage, int _spread, int _iTexture, int _numberShot, float _speed, bool _person) :
    person(_person),
    damage(_damage),
    speed(_speed)
{
    speed=_speed;
    srand(time(NULL));
    m_sprite.setTexture(vecTextures[_iTexture]);
    m_sprite.setPosition(_sprite->getPosition());
    angle = ((rand() % _spread - _spread / 2) + _sprite->getRotation()) / 180 * M_PI + ((float) _numberShot - 1.5) / 10;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::update()
{
    m_sprite.move(cos(angle) * 1000.f * speed * frameTime, sin(angle) * 1000.f * speed * frameTime);
}

float Projectile::getDamage()
{
    return damage;
}
void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
