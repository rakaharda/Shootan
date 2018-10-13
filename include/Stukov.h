#ifndef STUKOV_H
#define STUKOV_H

#include "Enemy.h"

class Stukov: public Enemy
{
    public:
        Stukov(int _xPos, int _yPos, const sf::Sprite* _sprite);
        virtual ~Stukov();
        virtual void update();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // STUKOV_H
