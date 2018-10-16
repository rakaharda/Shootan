#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

class Projectile : public GameObject
{
    public:
        enum ProjectileType
        {
            ptSprite,
            ptLine
        };
        Projectile(const sf::Sprite* _sprite, float _damage, int _spread, int _numberTexture, float _speed);
        Projectile(const sf::Sprite* _sprite, float _damage, int _spread, int _numberTexture, int _numberShot, float _speed);
        virtual ~Projectile();
        void update();
    private:
        float speed;
        float angle;
        float damage;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern float frameTime;
extern vector <sf::Texture> vecTextures;
extern sf::RenderWindow window;
#endif // PROJECTILE_H
