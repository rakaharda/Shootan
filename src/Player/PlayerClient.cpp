#include "Player/PlayerClient.h"

PlayerClient::PlayerClient()
{
    texture.loadFromFile("./data/player/sprite2.png");
    texture.setSmooth(true);
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, 
                       m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(FWIDTH / 2, FHEIGHT / 2);
    speed = 300.f;
    defaultSpeed = 300.f;
}

void PlayerClient::update(ClientEvents event)
{
    move(event);
}

void PlayerClient::update(sf::Vector2f _pos)
{
    m_sprite.setPosition(_pos);
}

void PlayerClient::move(ClientEvents event)
{
    float angle = -1;
    if(event.keyDownW && event.keyDownA)
    {
        angle = 5.f * M_PI / 4.f;
    }
    else if(event.keyDownS && event.keyDownA)
    {
        angle = 3.f * M_PI / 4.f;
    }
    else if(event.keyDownS && event.keyDownD)
    {
        angle = M_PI / 4.f;
    }
    else if(event.keyDownW && event.keyDownD)
    {
        angle = 7.f * M_PI / 4.f;
    }
    else
    {
        if(event.keyDownW)
        {
            angle = 3.f * M_PI / 2.f;
        }
        else if(event.keyDownS)
        {
            angle = M_PI / 2.f;
        }
        else if(event.keyDownA)
        {
            angle = M_PI;
        }
        else if(event.keyDownD)
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

void PlayerClient::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
PlayerClient::~PlayerClient()
{
    //dtor
}
