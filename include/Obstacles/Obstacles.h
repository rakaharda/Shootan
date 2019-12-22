#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "Components/GameObject.h"
#include "Player/Player.h"
#include "Utils/ResourceManager.h"


class Obstacles : public GameObject
{
    public:
        Obstacles();
        virtual ~Obstacles();
        virtual void smash(Player* &players) = 0;
        virtual void update() = 0;
        virtual bool checkActive() = 0;
        bool passability = true;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float frameTime;
extern ResourceManager      *resources;

#endif // OBSTACLES_H
