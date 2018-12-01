#include "Player/Player.h"

Player::Player() : HealthPoints()
{
    texture.loadFromFile("./data/player/sprite2.png");
    texture.setSmooth(true);
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(FWIDTH / 2, FHEIGHT / 2);
    weapon = new Weapon(&m_sprite);
    speed = 300.f;
    defaultSpeed = 300.f;
    upSpeed = 100.f;
    skill = 0;
    activeSpeedTime = 0.f;
    reloadTime = 0.f;
    projectileSpeed = 0.f;

}

Player::~Player()
{
    //dtor
}

void Player::update()
{
    setOrientation();
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        weapon->addProjectile();
    move();
    weapon->update();
    checkSkill();
}

void Player::setOrientation()
{
    float x;
    float y;
    //? x
    if(m_sprite.getPosition().x < window.getSize().x / 2.f)
        x = m_sprite.getPosition().x;
    else if(m_sprite.getPosition().x > FWIDTH - (window.getSize().x / 2.f))
        x = (float)(window.getSize().x) - FWIDTH + m_sprite.getPosition().x;
    else
        x = window.getSize().x / 2.f;
    //? y
    if(m_sprite.getPosition().y < window.getSize().y / 2.f)
        y = m_sprite.getPosition().y;
    else if(m_sprite.getPosition().y > FHEIGHT - (window.getSize().y / 2.f))
        y = (float)(window.getSize().y) - FHEIGHT + m_sprite.getPosition().y;
    else
        y = window.getSize().y / 2.f;

    m_sprite.setRotation(-180 / M_PI * atan2(
                             y - sf::Mouse::getPosition(window).y,
                             sf::Mouse::getPosition(window).x - x
                         ));
}

void Player::updatePerkWeapon()
{
    //reloadTime= reloadTime * 0.9f;
    //projectileSpeed+=0.02f;
    weapon->setReloadTime(weapon->getReloadTime() * 0.9f);
    weapon->setProjectileSpeed(weapon->getProjectileSpeed() + 0.02f);
    weapon->setCooldown(weapon->getCooldown()*0.9f);
}

void Player::handleEvents(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
        if((event.key.code == sf::Keyboard::R) && (weapon->getCurrentClipSize() != weapon->getClipSize()))
            weapon->reload();
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
    setSkill(skill);
}

void Player::setSkill(int _skill)
{
    if(skill == 0)
        skill = _skill;
        else if (skill != _skill)
                skill = 3;
    weapon->setSkill(skill);
}

void Player::checkSkill()
{
    if(activeSpeedTime > 0.f)
        activeSpeedTime -= frameTime;
    if(activeSpeedTime < 0.f)
    {
        activeSpeedTime = 0.f;
        speed -= upSpeed;
    }
}

void Player::move()
{
    float angle = -1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        angle = 5.f * M_PI / 4.f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        angle = 3.f * M_PI / 4.f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        angle = M_PI / 4.f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        angle = 7.f * M_PI / 4.f;
    }
    else
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            angle = 3.f * M_PI / 2.f;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            angle = M_PI / 2.f;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            angle = M_PI;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            angle = 0.f;
        }
    }
    if(angle != -1)
    {
        if(m_sprite.getPosition().x < 30.f)
            m_sprite.move( 1.f * speed * frameTime , sin(angle) * speed * frameTime);
        else if(m_sprite.getPosition().x > 3810.f)
            m_sprite.move( -1.f * speed * frameTime , sin(angle) * speed * frameTime);
        else if(m_sprite.getPosition().y < 30.f)
            m_sprite.move(cos(angle) * speed * frameTime, 1.f * speed * frameTime);
        else if(m_sprite.getPosition().y > 2130.f)
            m_sprite.move(cos(angle) * speed * frameTime, -1.f * speed * frameTime);
        else
            m_sprite.move(cos(angle) * speed * frameTime, sin(angle) * speed * frameTime);
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

float Player::getSpeed()
{
    return speed;
}

void Player::setSpeed(float _speed)
{
    speed = _speed;
}

float Player::getActiveSpeedTime()
{
    return activeSpeedTime;
}

void Player::setActiveSpeedTime(float _activeSpeedTime)
{
    activeSpeedTime = _activeSpeedTime;
}

float Player::getDefaultSpeed()
{
    return defaultSpeed;
}

float Player::getSpeedUp()
{
    return upSpeed;
}

void Player::setSpeedUp(float _speedUp)
{
    upSpeed = _speedUp;
}

void Player::setDefaultSpeed(float _defaultSpeed)
{
    defaultSpeed = _defaultSpeed;
}
