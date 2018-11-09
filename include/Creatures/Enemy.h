#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "Components/GameObject.h"
#include <iostream>
#include "Components/HealthPoints.h"
#include "Weapons/MeleeAttack.h"
#include "Weapons/Weapon.h"

using namespace std;

class Enemy : public GameObject, public HealthPoints
{
public:
    Enemy (const sf::Sprite* _sprite, float _healthPoints, sf::Texture& _texture);
    virtual ~Enemy();
    virtual void update();
    virtual void setWeapon(Weapon* _weapon);
    float        attack();
    void         setSkill(int _skill);
    void         setPosition(float _xPos, float _yPos);
    static float percentDamage;
    static float      FrostSpeed;
    static float      FrostRotationRate;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
    Weapon*           weapon;
    const sf::Sprite* target;
    float             rotationRate;
    float             speed;
    float             angle;
    float             currentAngle;
    float             distance;
    float             attackDistance;
    void move();
    void calculateRotation();
    bool checkDistance();
    void checkHealth();
    void checkSkill();
    int iFrost;
    float skillDamage;
    int skill;
    float skillTime;
    float currentSkillTime;
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <Projectile*> vecProjectiles;
#endif // ENEMY_H
