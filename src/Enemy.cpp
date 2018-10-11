#include "../include/Enemy.h"

Enemy::Enemy(int _xPos, int _yPos,const sf::Sprite* _sprite)
{
    texture.loadFromFile("./data/enemies/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setPosition(_xPos, _yPos);
    m_sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    player = _sprite;
    speed = 50.f;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::update()
{
    float angle = -180 / M_PI * atan2(
                        m_sprite.getPosition().y-player->getPosition().y,
                        player->getPosition().x-m_sprite.getPosition().x
                        );
    m_sprite.setRotation(angle);
    move(angle);
}

void Enemy::move(float angle)
{

    m_sprite.move(1 * speed * frameTime * sin(angle), 1 * speed * frameTime * cos(angle));
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    target.draw(m_sprite, states);
}
