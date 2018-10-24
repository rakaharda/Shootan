#include "CheckMark.h"

CheckMark::CheckMark(string _name, float _size, float _xPos, float _yPos, int _id)
{
    id = _id;
    texture.loadFromFile("./data/interface/markBG.png");
    markTexture.loadFromFile("./data/interface/mark.png");
    m_sprite.setTexture(texture);
    m_sprite.setPosition(_xPos - 130, _yPos - m_sprite.getTexture()->getSize().y / 2);
    markSprite.setTexture(markTexture);
    markSprite.setPosition(_xPos - 130, _yPos - m_sprite.getTexture()->getSize().y / 2);
    text.setString(_name);
    font.loadFromFile("./data/fonts/arial.ttf");
    text.setFont(font);
    text.setPosition(_xPos - 100,
                     _yPos - 20);
}


CheckMark::~CheckMark()
{
    //dtor
}

void CheckMark::update()
{

}

void CheckMark::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite,states);
    target.draw(text,states);
    if(isSelect)
        target.draw(markSprite,states);
}
