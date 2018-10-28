#ifndef PERK_H
#define PERK_H

#include "GameObject.h"

class Perk : public GameObject
{
    public:
        Perk(int _xPos, int _yPos);
        virtual ~Perk();
        void pickUp(){};
        void update();
        bool checkActive();
    protected:
        sf::Texture texture;
        float activeTime;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // PERK_H
