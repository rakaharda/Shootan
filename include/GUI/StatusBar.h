#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "SFML/Graphics.hpp"

class StatusBar : public sf::Drawable
{
public:
    StatusBar();
    virtual ~StatusBar();
    virtual void update() = 0;
protected:
    sf::Sprite   frame;
    sf::Vector2f origin;
    virtual void moveToOrigin();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // STATUSBAR_H
