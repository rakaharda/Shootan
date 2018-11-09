#include "GUI/Button.h"

Button::Button(sf::Texture& _texture, float _xPos, float _yPos)
{
    m_function = []{};
    m_sprite.setTexture(_texture);
    m_sprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x / 2, _yPos - m_sprite.getTexture()->getSize().y / 2);
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

void Button::changeButtonSprite(sf::Texture& _texture)
{
    m_sprite.setTexture(_texture);
}

void Button::setFunction(std::function <void()> _function)
{
    m_function = _function;
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
}

