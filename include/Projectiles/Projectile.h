#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Components/GameObject.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Projectile : public GameObject
{
public:
    enum ProjectileType
    {
        ptSprite,
        ptLine
    };
    Projectile(const sf::Sprite* _sprite, float _damage, int _spread, sf::Texture& _texture, float _speed, int _skill);
    Projectile(const sf::Sprite* _sprite, float _damage, int _spread, sf::Texture& _texture, int _numberShot, float _speed, int _skill);
    virtual ~Projectile();
    void  update();
    float getDamage();
    int getSkill();
private:
    float damage;
    float speed;
    float angle;
    int skill;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern float                frameTime;
extern sf::RenderWindow     window;
#endif // PROJECTILE_H
