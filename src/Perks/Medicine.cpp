#include "Perks/Medicine.h"

Medicine::Medicine(int _xPos, int _yPos) : Perk(_xPos, _yPos)
{
    m_sprite.setTexture(resources->getTexture("perk_cross"));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
}

void Medicine::pickUp()
{
    (player)->setCurrentHealthPoints((int)((player)->getHealthPoints()/4) + (player)->getCurrentHealthPoints());
    if((player)->getCurrentHealthPoints() > (player)->getHealthPoints())
        (player)->setCurrentHealthPoints( (player)->getHealthPoints() );
}
