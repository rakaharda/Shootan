#ifndef WEAPON_H
#define WEAPON_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include <list>
#include "Projectiles/Projectile.h"
#include "Components/Cooldown.h"
#include "Utils/ResourceManager.h"

using namespace std;

class Weapon : public Cooldown
{
public:
    Weapon(sf::Sprite* _source);
    virtual ~Weapon() {};
    virtual void  update();
    virtual bool  addProjectile();
    float         getReloadTime();
    float         getCurrentReloadTime();
    int           getClipSize();
    int           getCurrentClipSize();
    float         getAttackDistance();
    virtual float attack(){return 0.f;};
    void          getDamage() {};
    void          setDamage(float _damage) {};
    virtual void  setSkill(int _skill);
protected:
    const sf::Sprite* source;
    float             reloadTime;
    float             currentReloadTime;
    int               clipSize;
    int               currentClipSize;
    float             damage;
    int               spread;
    int               skill;
    float             projectileSpeed;
    float             wAttackDistance;
    string            textureKey;
    string            shotSoundKey;
    string            reloadSoundKey;
    list<sf::Sound>   sounds;
private:
};

extern sf::RenderWindow     window;
extern float                frameTime;
extern vector <Projectile*> vecProjectiles;
extern ResourceManager      *resources;
#endif // WEAPON_H
