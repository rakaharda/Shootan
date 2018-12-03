#include "Creatures/Enemy.h"

float Enemy::percentDamage = 0.05;
float Enemy::FrostSpeed = 130.f;
float Enemy::FrostRotationRate = 70.f;

Enemy::Enemy(const sf::Sprite* _sprite, float _healthPoints, sf::Texture& _texture) :
    HealthPoints(_healthPoints),
    attackDistance(-10.f)
{
    m_sprite.setTexture(_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, _texture.getSize().y,_texture.getSize().y));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().y / 2, m_sprite.getTexture()->getSize().y / 2);
    target = _sprite;
    angle = 180 / M_PI * atan2(
                target->getPosition().y - m_sprite.getPosition().y,
                target->getPosition().x - m_sprite.getPosition().x
            );
    m_sprite.setRotation(angle);
    currentAngle = angle;
    distance = (m_sprite.getPosition().x - target->getPosition().x) / cos(angle / 180 * M_PI);
    speed = 150.f;
    m_toDelete = false;
    m_isAlive = true;
    m_isBeingDestroyed = false;
    weapon = new MeleeAttack(&m_sprite);
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
    delete(weapon);
}

void Enemy::update()
{
    if(isAlive())
    {
        calculateRotation();
        m_sprite.setRotation(currentAngle);
        if(checkDistance())
            move();
        weapon->addProjectile();
        weapon->update();
        checkHealth();
        checkSkill();
        updateTexture();
    }
}
void Enemy::checkSkill()
{
    currentSkillTime -= frameTime;
    if(currentSkillTime < 0.f)
    {
        takeDamage(skillDamage);
        currentSkillTime = skillTime;
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
    if(abs(distance) > m_sprite.getTexture()->getSize().y / 2 + target->getTexture()->getSize().y / 2 + attackDistance)
        return true;
    return false;
}

void Enemy::checkHealth()
{
    if(currentHealthPoints == 0.f)
        kill();
}
void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
void Enemy::setWeapon(Weapon* _weapon)
{
    if(weapon != nullptr)
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
    else if(skill != _skill && _skill != 0)
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

Weapon* Enemy::getWeapon()
{
    return weapon;
}

void Enemy::updateTexture()
{
    if(skill == 3)
    {
        m_sprite.setTextureRect(sf::IntRect(m_sprite.getTexture()->getSize().y * 3, 0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
    }
    else if(skill == 1)
    {
        m_sprite.setTextureRect(sf::IntRect(m_sprite.getTexture()->getSize().y    , 0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
    }
    else if(skill == 2)
    {
        m_sprite.setTextureRect(sf::IntRect(m_sprite.getTexture()->getSize().y * 2, 0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
    }
    else
    {
        m_sprite.setTextureRect(sf::IntRect(0,                                      0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
    }
}

bool Enemy::isAlive()
{
    return m_isAlive;
}

bool Enemy::isBeingDestroyed()
{
    return m_isBeingDestroyed;
}

void Enemy::kill()
{
    m_isAlive = false;
}

void Enemy::destroy()
{
    m_isBeingDestroyed = true;
}

void Enemy::setSpeed(float _speed)
{
    speed = _speed;
}

float Enemy::getSpeed()
{
    return speed;
}
