#include "Player.h"

Player::Player()
{
    texture.loadFromFile("./data/player/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

Player::~Player()
{
    //dtor
}

void Player::update()
{
    m_sprite.setRotation(-180 / M_PI * atan2(
                        m_sprite.getPosition().y-sf::Mouse::getPosition(window).y,
                        sf::Mouse::getPosition(window).x-m_sprite.getPosition().x
                        ));
    move(70.f);
}

void Player::move(float speed)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_sprite.move(0.f, -1 * speed * frameTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_sprite.move(0.f, speed * frameTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_sprite.move(-1 * speed * frameTime, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_sprite.move(speed * frameTime, 0.f);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
