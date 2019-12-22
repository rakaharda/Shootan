#include "Obstacles/DeathZone.h"

DeathZone::DeathZone(int _xPos, int _yPos) : Obstacles()
{
    m_sprite.setTexture(resources->getTexture("obstacles_death_zone"));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
    passability = true;

}

void DeathZone::smash(Player* &players)
{
    if(timecounter <= 0.f)
    {
        players->takeDamage(5.f);
        timecounter = timereload;
    }
    else
    {
        timecounter -= frameTime;
    }

}


/*


*/
