#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include <iostream>
#include "Components/GameObject.h"
#include "Weapons/Weapon.h"
#include "Weapons/AssaultRifle.h"
#include "Weapons/Shotgun.h"
#include "Weapons/SniperRifle.h"
#include "Weapons/Gun.h"
#include "Components/HealthPoints.h"

//#define FHEIGHT 2160
//#define FWIDTH 3840

using namespace std;

class Player : public GameObject, public HealthPoints
{
public:
    Player();
    virtual ~Player();
    void    update();
    void    handleEvents(sf::Event event);
    Weapon* getWeapon();
    void    setWeapon(Weapon* _weapon);
    void    setSkill(int _skill);
    float   getSpeed();
    void    setSpeed(float _speed);
    float   getActiveSpeedTime();
    void    setActiveSpeedTime(float _activeSpeedtime);
    void    updatePerkWeapon();
    void    recline(int _x, int _y);
    float   getDefaultSpeed();
    float   getSpeedUp();
    void    setSpeedUp(float _speedUp);
    void    setDefaultSpeed(float _defaultSpeed);
    void    setBorders(float _width, float _height);
private:
    float FHEIGHT, FWIDTH;
    sf::Texture texture;
    Weapon*     weapon;
    Weapon*     newWeapon;
    int         skill;
    float       activeSpeedTime;
    float       reloadTime;
    float       projectileSpeed;
    float       speed;
    float       upSpeed;
    float       defaultSpeed;
    void         checkSkill();
    void         move();
    void         setOrientation();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void         checkWeapon();
};

extern sf::RenderWindow window;
extern float            frameTime;

#endif // PLAYER_H
