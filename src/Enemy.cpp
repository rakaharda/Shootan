#include "Enemy.h"

Enemy::Enemy(sf::Texture _texture, int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints, float _meleeDamage) : 
HealthPoints(_healthPoints),
MeleeAttack(_meleeDamage)
{
    texture = _texture;
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
    distance = (m_sprite.getPosition().x - player->getPosition().x) / cos(angle/180 * M_PI);
    speed = 50.f;
    toDelete = false;
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::update()
{
    checkHealth();
    calculateRotation();
    m_sprite.setRotation(currentAngle);
    if(checkDistance())
        move();
    reduceCooldown();
}

void Enemy::move()
{
    m_sprite.move(speed * frameTime * cos(currentAngle / 180 * M_PI), speed * frameTime * sin(currentAngle / 180 * M_PI));
}

void Enemy::calculateRotation()
{
    angle = 180 / M_PI * atan2(
                player->getPosition().y - m_sprite.getPosition().y,
                player->getPosition().x - m_sprite.getPosition().x
            );
    if(angle<0)
        angle += 360 ;
    if(currentAngle<0)
        currentAngle += 360;
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
        if(currentAngle>360.f)
            currentAngle -= 360.f;
    }
}

bool Enemy::checkDistance()
{
    distance = (m_sprite.getPosition().x - player->getPosition().x) / cos(angle/180 * M_PI);
    if(abs(distance) > m_sprite.getTexture()->getSize().x/2 + player->getTexture()->getSize().x/2)
        return true;
    return false;
}

void Enemy::checkHealth()
{
    if(currentHealthPoints == 0.f) 
        toDelete = true;
}
void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}

