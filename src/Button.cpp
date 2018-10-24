#include "Button.h"

Button::Button(string _name, string _path, float _xPos, float _yPos, int _id = 0)
{
    id = _id;
    texture.loadFromFile(_path);
    m_sprite.setTexture(texture);
    m_sprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x / 2, _yPos - m_sprite.getTexture()->getSize().y / 2);
    text.setString(_name);
    font.loadFromFile("./data/fonts/arial.ttf");
    text.setFont(font);
    text.setPosition(_xPos - _name.size()*14/2,
                     _yPos - 20);
}

Button::~Button()
{
    //dtor
}

void Button::changeButtonName(string _name)
{
    text.setString(_name);
    font.loadFromFile("./data/fonts/arial.ttf");
    text.setFont(font);
    text.setPosition(m_sprite.getPosition().x + m_sprite.getTexture()->getSize().x/2  - _name.size()*14/2,
                     m_sprite.getPosition().y + m_sprite.getTexture()->getSize().y/2  - 20);
}

void Button::changeButtonSprite(string _path)
{
    texture.loadFromFile(_path);
    m_sprite.setTexture(texture);
}

int Button::getID()
{
    return id;
}

void Button::setID(int _id)
{
    id = _id;
}

void Button::update()
{

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite,states);
    target.draw(text,states);
}

