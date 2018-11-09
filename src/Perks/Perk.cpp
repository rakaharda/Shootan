#include "Perks/Perk.h"
Player* Perk::player=NULL;
Perk::Perk(int _xPos, int _yPos)
{
    activeTime = 10.f;
    raz = 1.2f;
    currentTimeIncrease = 1.f;
    currentTimeTurn = 0.01f;
    timeIncrease1 = 1.f;
    timeIncrease2 = 0.1f;
    timeTurn = 0.01f;
    float angle;
    degree = 0;
    angle = degree / M_PI;
    m_sprite.setRotation(angle);
}
Perk::~Perk()
{
    //
}
void Perk::update()
{
    activeTime -= frameTime;
    currentTimeIncrease -= frameTime;
    currentTimeTurn -= frameTime;
    if(currentTimeTurn < 0.f)
    {
        float angle;
        degree++;
        angle = degree / M_PI;
        m_sprite.setRotation(angle);
        currentTimeTurn = timeTurn;
    }
    if(activeTime < 4.f)
    {
        timeIncrease1 = 0.5f;
    }
    if(currentTimeIncrease < 0.f)
    {
        m_sprite.scale(raz, raz);
        if(raz == 0.83333f)
        {
            raz = 1.2f;
            currentTimeIncrease = timeIncrease1;
        }
        else
        {
            raz = 0.83333f;
            currentTimeIncrease = timeIncrease2;
        }
    }
}
bool Perk::checkActive()
{
    if(activeTime <= 0)
        return 1;
    return 0;
}
void Perk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
