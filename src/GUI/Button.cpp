#include "GUI/Button.h"

Button::Button(sf::Texture& _texture, float _xPos, float _yPos)
{
    m_function = []{};
    m_sprite.setTexture(_texture);
    m_sprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x / 2, _yPos - m_sprite.getTexture()->getSize().y / 2);
    lightSprite = m_sprite;
    xPos = _xPos;
    yPos = _yPos;
    isLight = false;
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
        (*veclvl[i]).setPosition(xPos - 42 + i * 16, yPos + 23);
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

void Button::setLightButton(string name)
{
    lightSprite.setTexture(resources->getTexture(name));
    lightSprite.setPosition(m_sprite.getPosition());
}

void Button::update()
{
    if(m_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y)||
       lightSprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))
        isLight = true;
    else isLight = false;
}

void m_function()
{

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!isLight)
        target.draw(m_sprite,states);
    else target.draw(lightSprite,states);
    for (int i = 0; i < ilvl; i++)
    {
        target.draw((*veclvl[i]),states);
    }
}

