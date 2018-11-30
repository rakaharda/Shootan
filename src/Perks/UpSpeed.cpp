#include "Perks/UpSpeed.h"

UpSpeed::UpSpeed(int _xPos, int _yPos) : Perk(_xPos, _yPos)
{
    m_sprite.setTexture(resources->getTexture("perk_speedup"));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
}

void UpSpeed::pickUp()
{
    player->setActiveSpeedTime(30.f);
    if((player)->getSpeed() == (player)->getDefaultSpeed())
        (player)->setSpeed(player->getSpeed() + player->getSpeedUp());
}
