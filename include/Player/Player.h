#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "Components/GameObject.h"
#include "Weapons/Weapon.h"
#include "Weapons/Autorifle.h"
#include "Weapons/Shotgun.h"
#include "Weapons/SniperRifle.h"
#include "Weapons/Gun.h"
#include "Components/HealthPoints.h"

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
private:
    sf::Texture texture;
    float       speed;
    Weapon*     weapon;
    void         move();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;

#endif // PLAYER_H
