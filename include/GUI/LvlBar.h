#ifndef LVLBAR_H
#define LVLBAR_H

#include <SFML/Graphics.hpp>
#include "Utils/ResourceManager.h"
#include <iostream>

using namespace std;

class LvlBar : public sf::Drawable
{
public:
    LvlBar();
    virtual ~LvlBar();
    void update();
protected:
private:
    sf::Sprite   frame;
    sf::Sprite   lvlCells;
    sf::Vector2f origin;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;
extern ResourceManager  *resources;
#endif // LVLBAR_H
