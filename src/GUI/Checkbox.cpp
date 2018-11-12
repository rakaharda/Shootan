#include "GUI/CheckBox.h"
CheckBox::CheckBox(string _name, float _xPos, float _yPos, bool _isSelect)
    : Button(resources->getTexture("buttonSettingsMarkBorder"), _xPos, _yPos)
{
    m_sprite.setPosition(_xPos - 200, _yPos - m_sprite.getTexture()->getSize().y / 2);
    markSprite.setTexture(resources->getTexture("buttonSettingsMark"));
    markSprite.setPosition(_xPos - 200 + 5, _yPos - m_sprite.getTexture()->getSize().y / 2 + 5);
    font.loadFromFile("./data/fonts/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color(50,50,50));
    text.setString(_name);
    text.setCharacterSize(30);
    text.setPosition(_xPos - 35,
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
