#include "GUI/Button.h"

Button::Button(string _name, string _path, float _size, float _xPos, float _yPos, std::function<void(void)> _func)
{
    m_function = _func;
    texture.loadFromFile(_path);
    m_sprite.setTexture(texture);
    m_sprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x / 2, _yPos - m_sprite.getTexture()->getSize().y / 2);
    text.setString(_name);
    font.loadFromFile("./data/fonts/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(_size);
    text.setPosition(_xPos - _name.size()*14/2,
                     _yPos - 20);
}

Button::~Button()
{
    //dtor
}

bool Button::isClicked(float _xPos, float _yPos)
{
    if(m_sprite.getGlobalBounds().contains(_xPos, _yPos))
    {
        m_function();
        return true;
    }
    else return false;
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


void Button::update()
{

}

void m_function()
{

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite,states);
    target.draw(text,states);
}

