#include "Perks/Fire.h"

Fire::Fire(int _xPos, int _yPos) : Perk(_xPos, _yPos)
{
    m_sprite.setTexture(resources->getTexture("perk_fire"));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
}

void Fire::pickUp(Player* players)
{
    for(int i = 0; i < 60; i++)
        {
            vecProjectiles.push_back(new Projectile(players->getSpritePointer(), resources->getTexture("projectile_1"), i, 1));
        }
}
