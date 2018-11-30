#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML\Graphics.hpp>
#define M_PI 3.14159265359f

class GameObject : public sf::Drawable
{
public:
    GameObject() {m_toDelete = false;};
    virtual ~GameObject() {};
    virtual void update() = 0;
    bool         toDelete() {return m_toDelete;}
    void         markToDelete() {m_toDelete = true;}
    sf::Sprite   getSprite() {return m_sprite;}
    sf::Sprite*  getSpritePointer(){return &m_sprite;}
protected:
    sf::Sprite m_sprite;
    bool       m_toDelete;
};

#endif // GAMEOBJECT_H

