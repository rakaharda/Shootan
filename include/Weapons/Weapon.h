#ifndef WEAPON_H
#define WEAPON_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include "Projectiles/Projectile.h"
#include "Components/Cooldown.h"
using namespace std;

class Weapon : public Cooldown
{
public:
    Weapon(sf::Sprite* _player, bool _person = 0);
    Weapon(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize,float _damage, int _spread, bool _person=0);
    virtual ~Weapon(){};
    virtual void  update();
    virtual bool  addProjectile();
    float         getReloadTime();
    float         getCurrentReloadTime();
    int           getClipSize();
    int           getCurrentClipSize();
    float         getAttackDistance();
    virtual float attack() {return 0.f;};
    void          getDamage() {};
    void          setDamage(float _damage) {};
protected:
    const sf::Sprite* player;
    float             reloadTime;
    float             currentReloadTime;
    int               clipSize;
    int               currentClipSize;
    float             damage;
    int               spread;
    int               iTexture;
    float             projectileSpeed;
    float             wAttackDistance;
    bool              person;

private:
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <Projectile*> vecProjectiles;
#endif // WEAPON_H
