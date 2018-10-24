#ifndef CHECKMATK_H
#define CHECKMATK_H

#include "Button.h"

class CheckMark : public Button
{
public:
    CheckMark(string _name, float _size, float _xPos, float _yPos, int _id);
    virtual ~CheckMark();
    bool isSelect;
private:
    sf::Texture markTexture;
    sf::Sprite markSprite;
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //CHECKMATK_H