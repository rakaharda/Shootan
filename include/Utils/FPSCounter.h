#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <sstream>
#include <iostream>

class FPSCounter : public sf::Drawable
{
public:
    FPSCounter();
    FPSCounter operator++ ();
    void update();
private:
    int         counter;
    sf::Clock   clock;
    std::string s;
    sf::Text    text;
    sf::Font    font;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif // FPSCOUNTER_H
