#include "Projectiles/Projectile.h"

Projectile::Projectile(const sf::Sprite* _source, float _damage, int _spread, sf::Texture& _texture, float _speed, int _skill) :
    source(_source),
    damage(_damage),
    speed(_speed)
{
    toDelete = false;
    speed = _speed;
    skill = _skill;
    m_sprite.setTexture(_texture);
    m_sprite.setTextureRect(sf::IntRect(_texture.getSize().y * skill, 0, _texture.getSize().y, _texture.getSize().y));
    m_sprite.setOrigin(_texture.getSize().y / 2, _texture.getSize().y / 2);
    m_sprite.setPosition(source->getPosition().x + ((source->getTexture()->getSize().y + m_sprite.getTexture()->getSize().y) / 2.f * cos(source->getRotation() / 180.f * M_PI)),
                         source->getPosition().y + ((source->getTexture()->getSize().y + m_sprite.getTexture()->getSize().y) / 2.f * sin(source->getRotation() / 180.f * M_PI)));
    angle = ((rand() % _spread - _spread / 2) + source->getRotation()) / 180 * M_PI;
}

Projectile::Projectile(const sf::Sprite* _source, float _damage, int _spread, sf::Texture& _texture, int _numberShot, float _speed, int _skill) :
    Projectile(_source, _damage, _spread, _texture, _speed, _skill)
{

    angle = ((rand() % _spread - _spread / 2) + source->getRotation()) / 180 * M_PI + ((float) _numberShot - 1.5) / 20;
}
Projectile::Projectile(const sf::Sprite* _source, sf::Texture& _texture, int _numberShot, int _skill):
    Projectile(_source, 0.f, 2, _texture, 1.f, _skill)
{
    angle = (source->getRotation()) / 180 * M_PI + ((float) _numberShot) / M_PI * 6;

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

const sf::Sprite* Projectile::getSource()
{
    return source;
}
