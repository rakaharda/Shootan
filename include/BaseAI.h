#ifndef BASEAI_H
#define BASEAI_H

#include <SFML/Graphics.hpp>
#include <cmath>

class BaseAI{
    public:
        //BaseAI(sf::Sprite* m_sprite, sf::Sprite* player);
        BaseAI() {};
        virtual ~BaseAI() {};
        void update(sf::Sprite* m_sprite, sf::Sprite* player);
    protected:
        float angle;
        float currentAngle;
        float rotationRate;
        float distance;
        float speed;
        void move(sf::Sprite* m_sprite);
};

extern float frameTime;

#endif // BASEAI_H
