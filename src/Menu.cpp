#include "Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{
    //dor
}

void Menu::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed:
            window.close();
           // isPlaying = false;
            return;
        case sf::Event::KeyPressed:
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
                window.clear();
//                isPlaying = true;
                return;
            default:
                break;
            }
        case sf::Event::MouseButtonPressed:
            switch(event.mouseButton.button)
            {
                case sf::Mouse::Left:
                    searchButton();
                default:
                    break;
            }
        default:
            break;
        }
    }
}

void Menu::searchButton()
{
    for(unsigned int i = 0; i < buttons.size(); i++)
    {
        if(buttons[i]->m_sprite.getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y))
        {
            startProcess(buttons[i]->getId());
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
    for(unsigned int i = 0; i < buttons.size(); i++)
    target.draw(*buttons[i],states);
}
