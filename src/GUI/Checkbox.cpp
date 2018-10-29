#include "GUI/CheckBox.h"
CheckBox::CheckBox(string _name, float _size, float _xPos, float _yPos, int _id, bool _isSelect, std::function<void(void)> _func)
    : Button(_name, "./data/interface/markBG.png", _size, _xPos, _yPos, _func, _id)
{
    m_sprite.setPosition(_xPos - 100, _yPos - m_sprite.getTexture()->getSize().y / 2);
    markTexture.loadFromFile("./data/interface/mark.png");
    markSprite.setTexture(markTexture);
    markSprite.setPosition(_xPos - 100, _yPos - m_sprite.getTexture()->getSize().y / 2 - 5);
    text.setPosition(_xPos - 50,
                     _yPos - 20);
    isSelect = _isSelect;
}


CheckBox::~CheckBox()
{
    //dtor
}

void CheckBox::update()
{

}

void CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite,states);
    target.draw(text,states);
    if(isSelect)
    {
        target.draw(markSprite,states);
    }
}
