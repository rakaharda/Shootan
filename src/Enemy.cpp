#include "Enemy.h"

Enemy::Enemy(int _xPos, int _yPos,const sf::Sprite* _sprite)
{
    texture.loadFromFile("./data/enemies/sprite.png");
    m_sprite.setTexture(texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
    player = _sprite;
    angle = 180 / M_PI * atan2(
                        player->getPosition().y - m_sprite.getPosition().y,
                        player->getPosition().x - m_sprite.getPosition().x
                        );
    m_sprite.setRotation(angle);
    currentAngle = angle;
    rotationRate = 90.f;
    speed = 50.f;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::update()
{
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
    cout<<currentAngle<<' '<<angle<<endl;
    move();
}

void Enemy::move()
{
    m_sprite.move(speed * frameTime * cos(currentAngle / 180 * M_PI), speed * frameTime * sin(currentAngle / 180 * M_PI));
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
