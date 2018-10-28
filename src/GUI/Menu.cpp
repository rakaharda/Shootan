#include "GUI/Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{
    //dor
}

void Menu::processEvents(sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::Closed:
        window.close();
        return;
    case sf::Event::KeyPressed:
        switch(event.key.code)
        {
        default:
            break;
        }
    case sf::Event::MouseButtonPressed:
        switch(event.mouseButton.button)
        {
        case sf::Mouse::Left:
            searchButton();
            break;
        default:
            break;
        }
    default:
        break;
    }
}

void Menu::searchButton()
{
    for(unsigned int i = 0; i < buttons.size(); i++)
    {
        if(buttons[i]->m_sprite.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                sf::Mouse::getPosition(window).y))
        {
            startProcess(buttons[i]->getID());
            return;
        }
    }
}

void Menu::startProcess(int _id)
{
    switch(_id)
    {
    case 0:
        break;
    default:
        break;
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
