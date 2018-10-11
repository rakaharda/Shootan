#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "GameObject.h"

using namespace std;

class Enemy : public GameObject
{
    public:
        Enemy (int _xPos, int _yPos, const sf::Sprite* _sprite);
        virtual ~Enemy();
        void update();
    private:
        sf::Texture texture;
        const sf::Sprite* player;
        float speed;
        void move(float angle);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states);
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // ENEMY_H
