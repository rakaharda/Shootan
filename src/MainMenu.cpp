#include "MainMenu.h"
#include <iostream>
MainMenu::MainMenu(bool *_menuStatus)
{
    string str[4];
    str[0] = "Play";
    str[1] = "Settings";
    str[2] = "Exit";
    str[3] = "./data/interface/button.png";
    for(int i = 0; i < 3; i++)
        buttons.push_back(new Button(str[i],str[3],window.getSize().x / 2,window.getSize().y / 2 - 150 + i*150,i));
    for(int i = 0; i < 4; i++)
        str[i].erase();
    backGroundTexture.loadFromFile("./data/interface/background.png");
    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setPosition(window.getSize().x / 2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y / 2 - backGroundSprite.getTexture()->getSize().y / 2);
    menuStatus = _menuStatus;
    *menuStatus = true;
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::startProcess(int _id)
{
    switch(_id)
    {
    case 0:
        *menuStatus = false;
        return;

    case 2:
        window.close();
        return;
    default:
        break;
    }
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i]);
}
