#include "Perks/Frost.h"

Frost::Frost(int _xPos, int _yPos) : Perk(_xPos, _yPos)
{
    texture.loadFromFile("./data/perks/Blue.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
}

void Frost::pickUp()
{
    player->setSkill(2);
}
