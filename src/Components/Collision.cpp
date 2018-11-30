#include "Components/Collision.h"

bool Collision::checkCollision(GameObject* _obj, GameObject* _obj2)
{
    if(_obj->getSprite().getGlobalBounds().intersects(_obj2->getSprite().getGlobalBounds()))
        return true;
    return false;
}
