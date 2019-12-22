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
        float        setOrientation(float _angle = -1);
    protected:
        sf::Texture  texture;
        float        speed;
        float        defaultSpeed;
        void         move(ClientEvents event);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
};


extern sf::RenderWindow window;
extern float frameTime;
#endif // PLAYERCLIENT_H
