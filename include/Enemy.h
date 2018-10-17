#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "GameObject.h"
#include <iostream>
#include "HealthPoints.h"
#include "MeleeAttack.h"
using namespace std;

class Enemy : public GameObject, public HealthPoints, public MeleeAttack
{
public:
    Enemy (int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints, float _meleeDamage);
    virtual ~Enemy();
    virtual void update();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
    sf::Texture texture;
    const sf::Sprite* player;
    float speed;
    float angle;
    float currentAngle;
    float rotationRate;
    float distance;
    void move();
    void calculateRotation();
    bool checkDistance();
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // ENEMY_H
