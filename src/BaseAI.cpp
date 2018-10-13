#include "BaseAI.h"

/*BaseAI::BaseAI(sf::Sprite* m_sprite, sf::Sprite* player)
{
    angle = 180 / M_PI * atan2(
                        player->getPosition().y - m_sprite->getPosition().y,
                        player->getPosition().x - m_sprite->getPosition().x
                        );
    m_sprite->setRotation(angle);
    currentAngle = angle;
    rotationRate = 90.f;
    distance = (m_sprite->getPosition().x - player->getPosition().x) / cos(angle/180 * M_PI);
}*/
void BaseAI::update(sf::Sprite* m_sprite, sf::Sprite* player)
{
    distance = (m_sprite->getPosition().x - player->getPosition().x) / cos(angle/180 * M_PI);
    angle = 180 / M_PI * atan2(
                        player->getPosition().y - m_sprite->getPosition().y,
                        player->getPosition().x - m_sprite->getPosition().x
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
    m_sprite->setRotation(currentAngle);
    if(abs(distance) > m_sprite->getTexture()->getSize().x/2 + player->getTexture()->getSize().x/2)
        move(m_sprite);

}


void BaseAI::move(sf::Sprite* m_sprite)
{
    m_sprite->move(speed * frameTime * cos(currentAngle / 180 * M_PI), speed * frameTime * sin(currentAngle / 180 * M_PI));
}