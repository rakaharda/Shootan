#include "GUI/Button.h"

Button::Button(sf::Texture& _texture, float _xPos, float _yPos)
{
    m_function = []{};
    m_sprite.setTexture(_texture);
    m_sprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x / 2, _yPos - m_sprite.getTexture()->getSize().y / 2);
    xPos = _xPos;
    yPos = _yPos;
    ilvl = 0;
    textureLvl = resources->getTexture("buttonLVL");
}

Button::~Button()
{
    //dtor
}

void Button::setlvl(int _ilvl)
{
    if(ilvl > _ilvl)
    {
        veclvl.clear();
    }
    ilvl = _ilvl;
    for(int i = veclvl.size(); i < ilvl; i++)
    {
        veclvl.push_back(new sf::Sprite);
        (*veclvl[i]).setTexture(textureLvl);
        (*veclvl[i]).setPosition(xPos - 15 + i * 10 - (*veclvl[i]).getTexture()->getSize().x / 2, yPos + 15 - (*veclvl[i]).getTexture()->getSize().y / 2);
    }
}

void Button::setTextureButton(sf::Texture& _texture)
{
    m_sprite.setTexture(_texture);
    m_sprite.setPosition(xPos - m_sprite.getTexture()->getSize().x / 2, yPos - m_sprite.getTexture()->getSize().y / 2);
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
    for (int i = 0; i < ilvl; i++)
    {
        target.draw((*veclvl[i]),states);
    }
}

