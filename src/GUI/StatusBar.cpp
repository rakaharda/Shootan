#include "GUI/StatusBar.h"

StatusBar::StatusBar()
{
    //ctor
}

StatusBar::~StatusBar()
{
    //dtor
}

void StatusBar::moveToOrigin()
{
    frame.setPosition(origin);
}

void StatusBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
