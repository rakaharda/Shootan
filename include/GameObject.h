#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ObjectProperties.h"
#include <SFML\Graphics.hpp>

class GameObject : public sf::Drawable
{
    public:
        GameObject() {};
        virtual ~GameObject() {};
        virtual void update() = 0;
        virtual void processEvents(sf::Event event){};
        sf::Sprite m_sprite;
        ObjectProperties m_objectProperties;
    protected:

};

#endif // GAMEOBJECT_H

