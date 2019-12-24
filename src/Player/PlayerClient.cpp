#include "Player/PlayerClient.h"

PlayerClient::PlayerClient()
{
    
}

void PlayerClient::setOpponentTexture()
{
    texture.loadFromFile("./data/player/sprite3.png");
    texture.setSmooth(true);
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, 
                       m_sprite.getTexture()->getSize().y / 2);
}

void PlayerClient::update(ClientEvents event)
{
    move(event);
    update();
    if(event.keyDownLMB)
        weapon->addProjectile();
}

void PlayerClient::update(sf::Vector2f _pos, bool keyDownLMB)
{
    m_sprite.setPosition(_pos);
    update();
    if(keyDownLMB)
        weapon->addProjectile();
}

void PlayerClient::update()
{
    checkWeapon();
    weapon->update();
}

void PlayerClient::move(ClientEvents event)
{
    float angle = -1;
    if (event.keyDownW && event.keyDownA)
    {
        angle = 5.f * M_PI / 4.f;
    }
    else if (event.keyDownS && event.keyDownA)
    {
        angle = 3.f * M_PI / 4.f;
    }
    else if (event.keyDownS && event.keyDownD)
    {
        angle = M_PI / 4.f;
    }
    else if (event.keyDownW && event.keyDownD)
    {
        angle = 7.f * M_PI / 4.f;
    }
    else
    {
        if (event.keyDownW)
        {
            angle = 3.f * M_PI / 2.f;
        }
        else if (event.keyDownS)
        {
            angle = M_PI / 2.f;
        }
        else if (event.keyDownA)
        {
            angle = M_PI;
        }
        else if (event.keyDownD)
        {
            angle = 0.f;
        }
    }
    if (angle != -1)
    {
        if (m_sprite.getPosition().x < 30.f)
            m_sprite.move(1.f * speed * frameTime, sin(angle) * speed * frameTime);
        else if (m_sprite.getPosition().x > 3810.f)
            m_sprite.move(-1.f * speed * frameTime, sin(angle) * speed * frameTime);
        else if (m_sprite.getPosition().y < 30.f)
            m_sprite.move(cos(angle) * speed * frameTime, 1.f * speed * frameTime);
        else if (m_sprite.getPosition().y > 2130.f)
            m_sprite.move(cos(angle) * speed * frameTime, -1.f * speed * frameTime);
        else
            m_sprite.move(cos(angle) * speed * frameTime, sin(angle) * speed * frameTime);
    }
}

float PlayerClient::setOrientation(float _angle)
{
    float angle = _angle;
    if (angle == -1)
    {
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
        angle = -180 / M_PI * atan2(y - sf::Mouse::getPosition(window).y, sf::Mouse::getPosition(window).x - x);
    }
    m_sprite.setRotation(angle);
    return angle;
}

void PlayerClient::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
void PlayerClient::recline(int _x, int _y)
{
    m_sprite.setPosition(m_sprite.getPosition().x + _x, m_sprite.getPosition().y + _y);
}
PlayerClient::~PlayerClient()
{
    //dtor
}
