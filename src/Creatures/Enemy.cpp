#include "Creatures/Enemy.h"

float Enemy::percentDamage = 0.f;
float Enemy::FrostSpeed = 50.f;
float Enemy::FrostRotationRate = 90.f;

Enemy::Enemy(const sf::Sprite* _sprite, float _healthPoints, sf::Texture& _texture) :
    HealthPoints(_healthPoints),
    attackDistance(0.f)
{
    m_sprite.setTexture(_texture);
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    target = _sprite;
    angle = 180 / M_PI * atan2(
                target->getPosition().y - m_sprite.getPosition().y,
                target->getPosition().x - m_sprite.getPosition().x
            );
    m_sprite.setRotation(angle);
    currentAngle = angle;
    distance = (m_sprite.getPosition().x - target->getPosition().x) / cos(angle / 180 * M_PI);
    toDelete = false;
    weapon = NULL;
    speed = 50.f;
    rotationRate = 90.f;
    skillDamage = 0.f;
    skill = 0;
    skillTime = 1.f;
    currentSkillTime = skillTime;
}

void Enemy::setPosition(float _xPos, float _yPos)
{
    m_sprite.setPosition(_xPos, _yPos);
}
Enemy::~Enemy()
{

}

void Enemy::update()
{
    calculateRotation();
    m_sprite.setRotation(currentAngle);
    if(checkDistance())
        move();
    weapon->addProjectile();
    weapon->update();
    checkHealth();
    checkSkill();
}
void Enemy::checkSkill()
{
    currentSkillTime -= frameTime;
    if(currentSkillTime < 0.f)
    {
        takeDamage(skillDamage);
        currentSkillTime = skillTime;
        std::cout<<speed<<endl;
    }
}
void Enemy::move()
{
    m_sprite.move(speed * frameTime * cos(currentAngle / 180 * M_PI), speed * frameTime * sin(currentAngle / 180 * M_PI));
}

void Enemy::calculateRotation()
{
    angle = 180 / M_PI * atan2(
                target->getPosition().y - m_sprite.getPosition().y,
                target->getPosition().x - m_sprite.getPosition().x
            );
    if(angle < 0)
        angle += 360 ;
    if(currentAngle < 0)
        currentAngle += 360;
    if(currentAngle != angle)
    {
        if(abs(angle - currentAngle) < frameTime * rotationRate)
            currentAngle = angle;
        else
        {
            if(angle < currentAngle)
            {
                if ((360 + angle - currentAngle) < (currentAngle - angle))
                {
                    currentAngle += frameTime * rotationRate;
                }
                else
                    currentAngle -= frameTime * rotationRate;
            }
            else //(angle>=currentAngle)
            {
                if ((360 - angle + currentAngle) < (angle - currentAngle))
                {
                    currentAngle -= frameTime * rotationRate;
                }
                else
                    currentAngle += frameTime * rotationRate;
            }
        }
        if(currentAngle > 360.f)
            currentAngle -= 360.f;
    }
}

bool Enemy::checkDistance()
{
    distance = (m_sprite.getPosition().x - target->getPosition().x) / cos(angle / 180 * M_PI);
    if(abs(distance) > m_sprite.getTexture()->getSize().x / 2 + target->getTexture()->getSize().x / 2 + attackDistance)
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
void Enemy::setWeapon(Weapon* _weapon)
{
    if(weapon != NULL)
        delete(weapon);
    weapon = _weapon;
    attackDistance = weapon->getAttackDistance();
}

float Enemy::attack()
{
    return weapon->attack();
}

void Enemy::setSkill(int _skill)
{
    if(skill == 0)
    {
       skill = _skill;
    }
    else if(skill != _skill)
            {
                skill = 3;
            }
    if((skill == 2)||(skill == 3))
    {
        speed = FrostSpeed;
        rotationRate = FrostRotationRate;
    }
    if((skill == 1)||(skill == 3))
    {
        skillDamage = getHealthPoints() * percentDamage;
    }
}
