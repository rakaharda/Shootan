#include "Button.h"

Button::Button(string *_str,float _xPos, float _yPos, int _id)
{

}

Button::~Button()
{
    //dtor
}

int Button::getId()
{
    return id;
}

void Button::setID(int _id)
{
    id = _id;
}
