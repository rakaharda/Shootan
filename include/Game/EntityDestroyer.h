#ifndef ENTITYDESTROYER_H
#define ENTITYDESTROYER_H

#include <SFML/Graphics.hpp>
#include "Utils/ResourceManager.h"
#include "Creatures/Enemy.h"
#include "Components/GameObject.h"

class EntityDestroyer : public GameObject
{
    public:
        EntityDestroyer(Enemy* _enemyToDestroy);
        virtual ~EntityDestroyer();
        void update();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        Enemy* enemyToDestroy;
        float  destroyTimer;
        float  currentDestroyTimer;
        float  factor;
        sf::Sound sound;
};

extern float frameTime;
extern ResourceManager *resources;
extern AudioSettings   *audioSettings;
#endif // ENTITYDESTROYER_H
