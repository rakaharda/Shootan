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

#define FHEIGHT 2160
#define FWIDTH 3840

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
    float       speed;
    float       upSpeed;
    float       defoltSpeed;
    float       activeSpeedTime;
    void        checkSkill();
private:
    sf::Texture texture;
    Weapon*     weapon;
    int         skill;
    void         move();
    void         setOrientation();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;

#endif // PLAYER_H
