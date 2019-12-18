#include "GUI/TextBox.h"
#include <iostream>

TextBox::TextBox(string _name = "", float _xPos = 0, float _yPos = 0)
{
    m_sprite.setTexture(resources->getTexture("textBoxDefault"));
    m_sprite.setPosition(_xPos - m_sprite.getTexture()->getSize().x / 2, _yPos - m_sprite.getTexture()->getSize().y / 2);
    size = m_sprite.getTexture()->getSize().y / 2.5;
    m_text.setFillColor(sf::Color(60, 180, 240));
    m_text.setFont(resources->getFont("Mylodon-Light"));
    m_text.setCharacterSize(size);
    m_text.setString("A");
    setCenter();
    m_text.setString(_name);
    cursor.setTexture(resources->getTexture("cursorDefault"));
    moveCursor();
}

void TextBox::setFunction(std::function <void(void)> _func)
{
    m_function = _func;
}

string TextBox::getText()
{
    return m_text.getString();
}

void TextBox::handleEvents(sf::Event event)
{
    if(selected)
    {
        if(event.key.code == sf::Keyboard::Return)
        {
            m_function();
            selected = false;
        }
        else if(event.key.code == sf::Keyboard::BackSpace)
        {
            string str = m_text.getString();
            if(str.size() > 0)
            {
                str.pop_back();
                m_text.setString(str);
                auto bounds = m_text.getGlobalBounds();
                auto scale = m_text.getScale();
                if(scale.x < 1 && bounds.width / 0.9 + size < m_sprite.getTexture()->getSize().x)
                {
                    m_text.setScale(scale.x / 0.9, scale.y / 0.9 );
                    setCenter();
                }
                moveCursor();
            }
        }
        else if(event.type == sf::Event::TextEntered)
        {   if(event.key.code == sf::Keyboard::BackSpace)
                std::cout << "bckspc" << endl;
            string str = m_text.getString();
            if(str.size() < 15)
                str += event.text.unicode;
            m_text.setString(str);
            auto bounds = m_text.getGlobalBounds();
            if(bounds.width + size > m_sprite.getTexture()->getSize().x)
            {
                auto scale = m_text.getScale();
                m_text.setScale(scale.x * 0.9,scale.y * 0.9);
                setCenter();
            }
            moveCursor();
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        float _xPos = sf::Mouse::getPosition(window).x;
        float _yPos = sf::Mouse::getPosition(window).y;
        if(m_sprite.getGlobalBounds().contains(_xPos, _yPos))
        {
            selected = true;
        }
        else
        {
            selected = false;
        }
    }
}

void TextBox::update()
{
    float delay = clock.getElapsedTime().asSeconds();
    if(clock.getElapsedTime().asSeconds() > 0.8)
    {
        clock.restart();
        isFlick = false;
    }
    else if(selected && delay > 0.5)
    {
        isFlick = true;
    }

}

void TextBox::setCenter()
{
    auto textBounds = m_text.getGlobalBounds();
    auto backBounds = m_sprite.getGlobalBounds();
    //std::cout << backBounds.height << endl;
    m_text.setPosition(backBounds.left + size / 2, backBounds.top + backBounds.height / 2 - textBounds.height);
}

void TextBox::moveCursor()
{
    auto textBounds = m_text.getGlobalBounds();
    auto backBounds = m_sprite.getGlobalBounds();
    auto cursorBounds = cursor.getGlobalBounds();
    cursor.setPosition(textBounds.left + textBounds.width, backBounds.top + backBounds.height / 2 - cursorBounds.height / 2);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
    target.draw(m_text, states);
    if(isFlick)
    {
        target.draw(cursor, states);
    }

}
