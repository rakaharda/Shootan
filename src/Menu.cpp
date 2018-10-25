#include "Menu.h"

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
        if(buttons[i]->m_sprite.getGlobalBounds().contains(sf::Mouse::getPosition().x - buttons[i]->m_sprite.getTexture()->getSize().x/4,
                                                           sf::Mouse::getPosition().y - buttons[i]->m_sprite.getTexture()->getSize().y/2))
        {
            startProcess(buttons[i]->getID());
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
