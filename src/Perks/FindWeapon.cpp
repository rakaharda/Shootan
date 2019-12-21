#include "Perks/FindWeapon.h"

FindWeapon::FindWeapon(int _xPos, int _yPos, Weapon* _weapon) : Perk(_xPos, _yPos),
weapon(_weapon)
{
    //texture.loadFromFile("./data/perks/case.png");
    m_sprite.setTexture(resources->getTexture("perk_weapon"));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
}

void FindWeapon::pickUp(Player * players)
{
    players->setWeapon(weapon);
}
