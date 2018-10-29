#include "Player/Player.h"

Player::Player() : HealthPoints()
{
    texture.loadFromFile("./data/player/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(3840 / 2, 2160 / 2);
    weapon = new SniperRifle(&m_sprite);
    speed = 150.f;
}

Player::~Player()
{
    //dtor
}

void Player::update()
{
    //TODO: make it relative to player position relative to the screen
    m_sprite.setRotation(-180 / M_PI * atan2(
                             window.getSize().y / 2.f - sf::Mouse::getPosition(window).y,
                             sf::Mouse::getPosition(window).x - window.getSize().x / 2.f
                        ));
    move();
    weapon->update();
}

void Player::handleEvents(sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::MouseButtonPressed:
        switch(event.mouseButton.button)
        {
        case sf::Mouse::Left:
            weapon->addProjectile();
        default:
            break;
        }
        break;
    default:
        break;
    }
}

Weapon* Player::getWeapon()
{
    return weapon;
}

void Player::setWeapon(Weapon* _weapon)
{
    if(weapon != nullptr)
        delete(weapon);
    weapon = _weapon;
}

void Player::move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_sprite.move(0.f, -1 * speed * frameTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_sprite.move(0.f, speed * frameTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_sprite.move(-1 * speed * frameTime, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        m_sprite.move(speed * frameTime, 0.f);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        weapon->addProjectile();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
