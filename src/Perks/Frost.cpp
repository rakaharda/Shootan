#include "Perks/Frost.h"

Frost::Frost(int _xPos, int _yPos) : Perk(_xPos, _yPos)
{
    m_sprite.setTexture(resources->getTexture("perk_frost"));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
}

void Frost::pickUp()
{
    for(int i = 0; i < 60; i++)
        {
            vecProjectiles.push_back(new Projectile(player->getSpritePointer(), resources->getTexture("projectile_1"), i, 2));
        }
}
