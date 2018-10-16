#include "Collision.h"

bool Collision::checkCollision(GameObject* _obj, GameObject* _obj2)
{
    if(_obj->m_sprite.getGlobalBounds().intersects(_obj2->m_sprite.getGlobalBounds()))
        return true;
    return false;
}
