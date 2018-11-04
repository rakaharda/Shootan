#include "Perks/UpSpeed.h"

UpSpeed::UpSpeed(int _xPos, int _yPos) : Perk(_xPos, _yPos)
{
    texture.loadFromFile("./data/perks/run.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
}

void UpSpeed::pickUp()
{
    (player)->speed=300.f;
    (player)->activeSpeedTime=30.f;
}
