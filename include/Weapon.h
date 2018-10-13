#ifndef WEAPON_H
#define WEAPON_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <cmath>
#include "../include/Projectile.h"

using namespace std;

class Weapon
{
    public:
        Weapon(sf::Sprite* _player);
        Weapon(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize,float _damage, int _spread, Projectile::ProjectileType _projectileType);
        virtual ~Weapon();
        void update();
        virtual bool addProjectile();
        float getReloadTime();
        float getCurrentReloadTime();
        float getCooldown();
        float getCurrentCooldown();
        int getClipSize();
        int getCurrentClipSize();
    protected:
        const sf::Sprite* player;
        float weaponCooldown;
        float currentCooldown;
        float reloadTime;
        float currentReloadTime;
        int clipSize;
        int currentClipSize;
        float damage;
        int spread;
        Projectile::ProjectileType projectileType;
    private:
};
class WeaponAutorifle: public Weapon{
    public:
        WeaponAutorifle(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize,float _damage, int _spread, Projectile::ProjectileType _projectileType);
};
class WeaponShotgun{
    public:
        WeaponShotgun(sf::Sprite* _player, float _weaponCooldown, float _reloadTime, int _clipSize,float _damage, int _spread, Projectile::ProjectileType _projectileType);
        bool addProjectile();
};
extern sf::RenderWindow window;
extern float frameTime;
extern vector <GameObject*> vecProjectiles;
#endif // WEAPON_H