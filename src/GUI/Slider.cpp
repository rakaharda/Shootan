#include "Slider.h"
#include <iostream>
Slider::Slider(string _name, float _xPos, float _yPos, float _status)
{
    m_function = [](float status){};
    status = _status;
    pressed = false;
    lineSprite.setTexture(resources->getTexture("sliderLine"));
    m_sprite.setTexture(resources->getTexture("sliderButton"));
    lineSprite.setPosition(_xPos - lineSprite.getTexture()->getSize().x / 2,
                           _yPos - lineSprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(lineSprite.getPosition().x + status, _yPos - lineSprite.getTexture()->getSize().y / 2);
}

Slider::~Slider()
{
    //dtor
}

bool Slider::isPressed(float _xPos, float _yPos)
{
    if(m_sprite.getGlobalBounds().contains(_xPos, _yPos ))
        pressed = true;
    if(pressed)
    {
        status = _xPos - lineSprite.getPosition().x;
        cout << status << endl;
        if(status >= 0 && status <= 200)
            m_sprite.move(_xPos - m_sprite.getPosition().x - m_sprite.getTexture()->getSize().x / 2, 0);
        else if(status > 200)
        {
            status = 200.f;
            m_sprite.setPosition(lineSprite.getPosition().x + status,
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
}

