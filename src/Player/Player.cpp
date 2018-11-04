#include "Player/Player.h"

Player::Player() : HealthPoints()
{
    texture.loadFromFile("./data/player/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(FWIDTH / 2, FHEIGHT / 2);
    weapon = nullptr;
    speed = 200.f;
    skill = 0;
    activeSkillTimeFire=0.f;
    activeSkillTimeFrost=0.f;
    activeSpeedTime=0.f;
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

void Player::handleEvents(sf::Event event)
{

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
    if(_skill == 1)
        activeSkillTimeFire = 30.f;
    if(_skill == 2)
        activeSkillTimeFrost = 30.f;
    if((activeSkillTimeFire > 0.f) && (activeSkillTimeFrost > 0.f))
        skill = 3;
    else
        skill = _skill;
    weapon->setSkill(skill);
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
            weapon->setSkill(skill);
        }
        if(activeSkillTimeFrost<=0.f)
        {
            activeSkillTimeFrost=0.f;
            skill=1;
            weapon->setSkill(skill);
        }
    }
    if((activeSkillTimeFire<=0.f)&&(activeSkillTimeFrost<=0.f))
    {
        activeSkillTimeFire=0.f;
        activeSkillTimeFrost=0.f;
        setSkill(0);
    }
    if(activeSpeedTime>0.f)
        activeSpeedTime-=frameTime;
    if(activeSpeedTime<0.f)
    {
        activeSpeedTime=0.f;
        speed=200.f;
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
        m_sprite.move(cos(angle) * speed * frameTime, sin(angle) * speed * frameTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
