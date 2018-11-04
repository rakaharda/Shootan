#include "Perks/Perk.h"
Player* Perk::player=NULL;
Perk::Perk(int _xPos, int _yPos)
{
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
