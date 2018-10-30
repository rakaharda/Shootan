#include "Player/Player.h"

Player::Player() : HealthPoints()
{
    texture.loadFromFile("./data/player/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(FWIDTH / 2, FHEIGHT / 2);
    weapon = new SniperRifle(&m_sprite);
    speed = 200.f;
}

Player::~Player()
{
    //dtor
}

void Player::update()
{
    //TODO: make it relative to player position relative to the screen
    float x;
    float y;
    //? x
    if (m_sprite.getPosition().x < window.getSize().x / 2.f)
        x = m_sprite.getPosition().x;
    else if (m_sprite.getPosition().x > FWIDTH - (window.getSize().x / 2.f))
        x = (float)(window.getSize().x) - FWIDTH + m_sprite.getPosition().x;
    else 
        x = window.getSize().x / 2.f;
    //? y
    if (m_sprite.getPosition().y < window.getSize().y / 2.f)
        y = m_sprite.getPosition().y;
    else if (m_sprite.getPosition().y > FHEIGHT - (window.getSize().y / 2.f))
        y = (float)(window.getSize().y) - FHEIGHT + m_sprite.getPosition().y;
    else 
        y = window.getSize().y / 2.f;

    m_sprite.setRotation(-180 / M_PI * atan2(
                             y - sf::Mouse::getPosition(window).y,
                             sf::Mouse::getPosition(window).x - x
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
