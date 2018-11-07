#include "Creatures/Enemy.h"

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
    rotationRate = 90.f;
    distance = (m_sprite.getPosition().x - target->getPosition().x) / cos(angle / 180 * M_PI);
    speed = 150.f;
    toDelete = false;
    weapon = new MeleeAttack(&m_sprite);
    iFrost = 0;
    iFire = 0;
    skillDamage = 0.f;
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
    calculateRotation();
    m_sprite.setRotation(currentAngle);
    if(checkDistance())
        move();
    weapon->addProjectile();
    weapon->update();
    checkHealth();
    checkSkill();
    takeDamage(skillDamage);
    updateTexture();
}
void Enemy::checkSkill()
{
    for (unsigned int i = 0; i < vecSkills.size();i++)
    {
        vecSkills[i]->skillTime -= frameTime;
        if(vecSkills[i]->skillTime <=0.f)
        {
            if(vecSkills[i]->skill == 1)
            {
                iFire--;
                skillDamage-=0.01f;
                vecSkills.erase(vecSkills.begin() + i);
            }
            if(vecSkills[i]->skill == 2)
            {

                iFrost--;
                rotationRate+=8.f;
                speed+=5.f;
                vecSkills.erase(vecSkills.begin() + i);
            }
        }
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
        toDelete = true;
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
    if(((_skill == 1)||(_skill == 3)) && (iFire < 10))
    {
        skills *sk=new skills;
        sk->skillTime = 5.f;
        sk->skill = 1;
        skillDamage += 0.01f;
        vecSkills.push_back(sk);
        iFire++;
    }
    if(((_skill == 2) || (_skill == 3)) && (iFrost < 10))
    {
        skills *sk = new skills;
        sk->skillTime = 5.f;
        sk->skill = 2;
        rotationRate -= 8.f;
        speed -= 5.f;
        vecSkills.push_back(sk);
        iFrost++;
    }
}

Weapon* Enemy::getWeapon()
{
    return weapon;
}

void Enemy::updateTexture()
{
    if(iFrost > 0 && iFire > 0)
    {
        m_sprite.setTextureRect(sf::IntRect(m_sprite.getTexture()->getSize().y * 3, 0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
        m_sprite.setOrigin(m_sprite.getTexture()->getSize().y * 3 + m_sprite.getTexture()->getSize().y / 2, m_sprite.getTexture()->getSize().y / 2);
    }
    else if(iFire > 0)
    {
        m_sprite.setTextureRect(sf::IntRect(m_sprite.getTexture()->getSize().y    , 0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
        m_sprite.setOrigin(m_sprite.getTexture()->getSize().y + m_sprite.getTexture()->getSize().y / 2, m_sprite.getTexture()->getSize().y / 2);
    }
    else if(iFrost > 0)
    {
        m_sprite.setTextureRect(sf::IntRect(m_sprite.getTexture()->getSize().y * 2, 0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
        m_sprite.setOrigin(m_sprite.getTexture()->getSize().y * 2 + m_sprite.getTexture()->getSize().y / 2, m_sprite.getTexture()->getSize().y / 2);
    }
    else
    {
        m_sprite.setTextureRect(sf::IntRect(0,                                      0, m_sprite.getTexture()->getSize().y, m_sprite.getTexture()->getSize().y));
        m_sprite.setOrigin(m_sprite.getTexture()->getSize().y / 2, m_sprite.getTexture()->getSize().y / 2);
    }
}