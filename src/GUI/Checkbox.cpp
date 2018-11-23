#include "GUI/CheckBox.h"
CheckBox::CheckBox(string _name, float _xPos, float _yPos, bool _isSelect)
    : Button(resources->getTexture("buttonSettingsMarkBorder"), _xPos, _yPos)
{
    m_sprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x/2, _yPos - m_sprite.getTexture()->getSize().y / 2);
    markSprite.setTexture(resources->getTexture("buttonSettingsMark"));
    markSprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x/2 + 5, _yPos - m_sprite.getTexture()->getSize().y / 2 + 5);
    textSprite.setTexture(resources->getTexture(_name));
    textSprite.setPosition(_xPos + textSprite.getTexture()->getSize().x/8,
                     _yPos - textSprite.getTexture()->getSize().y/2);
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
    target.draw(textSprite,states);
    if(isSelect)
    {
        target.draw(markSprite,states);
    }
}
