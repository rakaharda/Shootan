#include "Projectiles/Projectile.h"

Projectile::Projectile(const sf::Sprite* _sprite, float _damage, int _spread, sf::Texture& _texture, float _speed, int _skill) :
    damage(_damage),
    speed(_speed)
{
    toDelete = false;
    speed = _speed;
    skill = _skill;
    m_sprite.setTexture(_texture);
    m_sprite.setTextureRect(sf::IntRect(_texture.getSize().y * skill, 0, _texture.getSize().y, _texture.getSize().y));
    m_sprite.setOrigin(_texture.getSize().y / 2, _texture.getSize().y / 2);
    m_sprite.setPosition(_sprite->getPosition().x + ((_sprite->getTexture()->getSize().y + m_sprite.getTexture()->getSize().y / 2.f) * cos(_sprite->getRotation() / 180.f * M_PI)),
                         _sprite->getPosition().y + ((_sprite->getTexture()->getSize().y + m_sprite.getTexture()->getSize().y / 2.f) * sin(_sprite->getRotation() / 180.f * M_PI)));
    angle = ((rand() % _spread - _spread / 2) + _sprite->getRotation()) / 180 * M_PI;
}

Projectile::Projectile(const sf::Sprite* _sprite, float _damage, int _spread, sf::Texture& _texture, int _numberShot, float _speed, int _skill) :
    Projectile(_sprite, _damage, _spread, _texture, _speed, _skill)
{

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

int Projectile::getSkill()
{
    return skill;
}
