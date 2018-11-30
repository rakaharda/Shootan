#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML\Graphics.hpp>
#define M_PI 3.14159265359f

class GameObject : public sf::Drawable
{
public:
    GameObject() {toDelete = false;};
    virtual ~GameObject() {};
    virtual void update() = 0;
    sf::Sprite       m_sprite;
    bool             toDelete;
protected:

};

#endif // GAMEOBJECT_H

