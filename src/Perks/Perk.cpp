#include "Perks/Perk.h"

Perk::Perk(int _xPos, int _yPos)
{
    texture.loadFromFile("./data/perks/defolt.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
    activeTime=10.f;
}
Perk::~Perk()
{
    //
}
void Perk::update()
{
    activeTime-=frameTime;
}
bool Perk::checkActive()
{
    if(activeTime<=0)
        return 1;
    return 0;
}
void Perk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
