#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "GUI/Button.h"

class CheckBox : public Button
{
public:
    CheckBox(string _name, float _size, float _xPos, float _yPos, int _id, bool _isSelect, std::function<void(void)> _func);
    virtual ~CheckBox();
private:
    sf::Texture markTexture;
    sf::Sprite markSprite;
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //CHECKBOX_H