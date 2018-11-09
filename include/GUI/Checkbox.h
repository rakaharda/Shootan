#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "GUI/Button.h"
#include "Utils/ResourceManager.h"

class CheckBox : public Button
{
public:
    CheckBox(string _name, float _xPos, float _yPos, bool _isSelect);
    virtual ~CheckBox();
private:
    sf::Sprite markSprite;
    sf::Font font;
    sf::Text text;
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern ResourceManager *resources;
#endif //CHECKBOX_H
