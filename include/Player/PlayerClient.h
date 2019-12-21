#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include <cmath>
#include <iostream>
#include "Components/GameObject.h"
#include "Components/ClientEvents.h"
#include "Components/HealthPoints.h"

#define FHEIGHT 2000
#define FWIDTH 2000

using namespace std;

class PlayerClient : public GameObject, public HealthPoints
{
    public:
        PlayerClient();
        virtual ~PlayerClient();
        void update(ClientEvents event);
        void update(sf::Vector2f _pos);
        void update(){};
    protected:
        sf::Texture  texture;
        float        speed;
        float        defaultSpeed;
        void         move(ClientEvents event);
        void         setOrientation();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
};


extern sf::RenderWindow window;
extern float frameTime;
#endif // PLAYERCLIENT_H
