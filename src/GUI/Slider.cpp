#include "GUI/Slider.h"
#include <iostream>
#define INDENT 10.f
Slider::Slider(string _name, float _xPos, float _yPos, float _status)
{
    m_function = [](float status){};
    status = _status;
    pressed = false;
    index = 100.f/(resources->getTexture("sliderLine").getSize().x - 2*INDENT);
    lineSprite.setTexture(resources->getTexture("sliderLine"));
    textSprite.setTexture(resources->getTexture(_name));
    m_sprite.setTexture(resources->getTexture("sliderButton"));
    lineSprite.setPosition(_xPos - lineSprite.getTexture()->getSize().x / 2,
                           _yPos - lineSprite.getTexture()->getSize().y / 2);
    textSprite.setPosition(_xPos - textSprite.getTexture()->getSize().x / 2,
                           _yPos - textSprite.getTexture()->getSize().y / 2 - INDENT / index);
    m_sprite.setPosition(lineSprite.getPosition().x + status/index, _yPos - lineSprite.getTexture()->getSize().y / 2);
}

Slider::~Slider()
{
    //dtor
}

bool Slider::isPressed()
{
    float _xPos = sf::Mouse::getPosition(window).x;
    float _yPos = sf::Mouse::getPosition(window).y;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        if(m_sprite.getGlobalBounds().contains(_xPos, _yPos))
            pressed = true;
        else;
    else pressed = false;
    if(pressed)
    {
        status = (_xPos - lineSprite.getPosition().x - INDENT) * index;
        if(status >= 0 && status <= 100)
            m_sprite.move(_xPos - m_sprite.getPosition().x - m_sprite.getTexture()->getSize().x / 2, 0);
        else if(status > 100)
        {
            status = 100.f;
            m_sprite.setPosition(lineSprite.getPosition().x + status / index,
            lineSprite.getPosition().y);
        }
        else if (status < 0)
        {
            status = 0.f;
            m_sprite.setPosition(lineSprite.getPosition().x,
            lineSprite.getPosition().y );
        }
        m_function(status);
        return true;
    }
    else return false;
}

void Slider::setFunction(std::function <void(float)> _function)
{
    m_function = _function;
}


void Slider::update()
{

}

void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(lineSprite,states);
    target.draw(m_sprite,states);
    target.draw(textSprite,states);
}

