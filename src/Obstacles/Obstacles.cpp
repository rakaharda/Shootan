#include "Obstacles/Obstacles.h"

Obstacles::Obstacles()
{

}
Obstacles::~Obstacles()
{
    //
}

void Obstacles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
