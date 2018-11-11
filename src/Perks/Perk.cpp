#include "Perks/Perk.h"
Player* Perk::player=NULL;
Perk::Perk(int _xPos, int _yPos)
{
    activeTime = 15.f;
    raz = 1.1f;
    currentTimeIncrease = 1.f;
    currentTimeTurn = 0.01f;
    timeIncrease1 = 1.f;
    timeIncrease2 = 0.03f;
    timeTurn = 0.01f;
    float angle;
    degree = 0;
    angle = degree / M_PI;
    m_sprite.setRotation(angle);
    iAnimation=0;
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
    if(activeTime < 2.f)
    {
        if(currentTimeIncrease < 0.f)
        {
            m_sprite.scale(0.9f, 0.9f);
            currentTimeIncrease = 0.1;
        }
        if(currentTimeTurn < 0.f)
        {
            float angle;
            degree +=5;
            angle = degree / M_PI;
            m_sprite.setRotation(angle);
            currentTimeTurn = 0.001f;
        }
        return ;
    }
    if(currentTimeTurn < 0.f)
    {
        float angle;
        degree++;
        angle = degree / M_PI;
        m_sprite.setRotation(angle);
        currentTimeTurn = timeTurn;
    }
    if(activeTime < 6.f)
    {
        timeIncrease1 = 0.5f;
    }
    if(currentTimeIncrease < 0.f)
    {
        m_sprite.scale(raz, raz);
        iAnimation++;
        currentTimeIncrease = timeIncrease2;
        if (iAnimation == 3)
        {
            raz = 0.90909091;
        }
        if (iAnimation == 6)
        {
            iAnimation = 0;
            raz = 1.1f;
            currentTimeIncrease = timeIncrease1;
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
