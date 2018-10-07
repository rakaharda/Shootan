#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
    public:
        Player();
        virtual ~Player();
        void ProcessEvents();
        void update();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PLAYER_H
