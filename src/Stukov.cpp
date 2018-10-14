#include "Stukov.h"

GroundExplosionSpell::GroundExplosionSpell(const sf::Sprite* _sprite)
{
    xPos = _sprite->getPosition().x;
    yPos = _sprite->getPosition().y;
    phase = 1.f;
    castSpeed = 2.f;
    texture.loadFromFile("./data/spells/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setPosition(xPos,yPos);
    m_sprite.setTextureRect(sf::IntRect(0,0,1,1));
}

GroundExplosionSpell::~GroundExplosionSpell()
{
    //dtor
}
void GroundExplosionSpell::update()
{
    m_sprite.setScale(castSpeed*frameTime, castSpeed*frameTime);
        phase++;
}

void GroundExplosionSpell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}



Stukov::Stukov(int _xPos, int _yPos, const sf::Sprite* _sprite): Enemy(_xPos, _yPos, _sprite)
{
    /*castTime = 3.f;
    isCasted = false;
    m_spell = new GroundExplosionSpell(player); */
}

Stukov::~Stukov()
{
    //dtor
}

void Stukov::update()
{
/*    if(rand()%100)
    {
        isCasted = true;
        m_spell = new GroundExplosionSpell(player);
    }
    if(isCasted)
        if (m_spell.phase > 30)
        {
            delete(m_spell);
            isCasted = false;
        }
        */
    distance = (m_sprite.getPosition().x - player->getPosition().x) / cos(angle/180 * M_PI);
    angle = 180 / M_PI * atan2(
                        player->getPosition().y - m_sprite.getPosition().y,
                        player->getPosition().x - m_sprite.getPosition().x
                        );
    if(angle<0) angle += 360 ;
    if(currentAngle<0) currentAngle += 360;
    if(currentAngle != angle)
        {
            if(abs(angle-currentAngle) < frameTime * rotationRate)
                currentAngle = angle;
            else
            {
                if(angle<currentAngle)
                {
                    if ((360+angle-currentAngle)<(currentAngle-angle))
                    {
                        currentAngle += frameTime * rotationRate;
                    }
                    else
                        currentAngle -= frameTime * rotationRate;
                }
                else //(angle>=currentAngle)
                {
                    if ((360-angle+currentAngle)<(angle-currentAngle))
                    {
                        currentAngle -= frameTime * rotationRate;
                    }
                    else
                        currentAngle += frameTime * rotationRate;
                }
            }
        if(currentAngle>360.f) currentAngle -= 360.f;
        }
    m_sprite.setRotation(currentAngle);
    if(abs(distance) > m_sprite.getTexture()->getSize().x/2 + player->getTexture()->getSize().x/2)
        move();
}

void Stukov::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
//    if(isCasted)
//       target.draw(*m_spell);
}

