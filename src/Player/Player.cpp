#include "Player/Player.h"

Player::Player() : HealthPoints()
{
    texture.loadFromFile("./data/player/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    weapon = new SniperRifle(&m_sprite);
    speed = 150.f;
    skill=0;
    activeSkillTimeFire=0.f;
    activeSkillTimeFrost=0.f;
}

Player::~Player()
{
    //dtor
}

void Player::update()
{
    m_sprite.setRotation(-180 / M_PI * atan2(

                             m_sprite.getPosition().y - sf::Mouse::getPosition(window).y,
                             sf::Mouse::getPosition(window).x - m_sprite.getPosition().x
                        ));
    move();
    weapon->update();
    checkSkill();


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
    if(weapon != NULL)
        delete(weapon);
    weapon = _weapon;
    setSkill(skill);
}

void Player::setSkill(int _skill)
{
    if(_skill == 1)
        activeSkillTimeFire = 30.f;
    if(_skill == 2)
        activeSkillTimeFrost = 30.f;
    if((activeSkillTimeFire > 0.f) && (activeSkillTimeFrost > 0.f))
        skill = 3;
    else
        skill = _skill;
    weapon->setITexture(skill);
}

void Player::checkSkill()
{
    if(skill==1)
        activeSkillTimeFire-=frameTime;
    if(skill==2)
        activeSkillTimeFrost-=frameTime;
    if(skill==3)
    {
        activeSkillTimeFire-=frameTime;
        activeSkillTimeFrost-=frameTime;
        if(activeSkillTimeFire<=0.f)
        {
            activeSkillTimeFire=0.f;
            skill=2;
            weapon->setITexture(skill);
        }
        if(activeSkillTimeFrost<=0.f)
        {
            activeSkillTimeFrost=0.f;
            skill=1;
            weapon->setITexture(skill);
        }
    }
    if((activeSkillTimeFire<=0.f)&&(activeSkillTimeFrost<=0.f))
    {
        activeSkillTimeFire=0.f;
        activeSkillTimeFrost=0.f;
        setSkill(0);
    }
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
