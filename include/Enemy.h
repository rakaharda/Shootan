#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "GameObject.h"
#include <iostream>
#include "HealthPoints.h"
#include "MeleeAttack.h"
#include "Weapon.h"
using namespace std;

class Enemy : public GameObject, public HealthPoints
{
    public:
        Enemy (int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints);
        virtual ~Enemy();
        virtual void update();
        virtual void setWeapon(Weapon* _weapon);
        float attack();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    protected:
        Weapon * weapon;
        sf::Texture texture;
        const sf::Sprite* player;
        float speed;
        float angle;
        float currentAngle;
        float rotationRate;
        float distance;
        float distanceAttack;
        void move();
        void calculateRotation();
        bool checkDistance();
};

extern sf::RenderWindow window;
extern float frameTime;
extern vector <sf::Texture> vecTextures;
extern vector <Projectile*> vecProjectiles;
#endif // ENEMY_H
