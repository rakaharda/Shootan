#include "MainMenu.h"
#include <iostream>
MainMenu::MainMenu(bool *_menuStatus, bool *_fullscreen, bool *_verticalSync)
{
    isSettings = false;
    verticalSync = _verticalSync;
    fullscreen = _fullscreen;
    string str[4];
    str[0] = "Play";
    str[1] = "Settings";
    str[2] = "Exit";
    str[3] = "./data/interface/button.png";
    for(int i = 0; i < 3; i++)
        buttons.push_back(new Button(str[i],str[3],30.f,window.getSize().x / 2,window.getSize().y / 2 - 150 + i*150,i));
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
    case 1:
        createSettingsMenu();
        //sf::sleep(sf::microseconds(5000000));
        return;
    case 2:
        window.close();
        return;
    case 3:
        if (*verticalSync)
        {
            buttons[0]->isSelect = *verticalSync =  false;
            window.setVerticalSyncEnabled(false);
        }
        else
        {
            buttons[0]->isSelect = *verticalSync = true;
            window.setVerticalSyncEnabled(true);
        }
        break;
    case 4:
        if(*fullscreen)
        {
            window.close();
            window.create(sf::VideoMode(1280, 720), "Shootan");
            if (*verticalSync)
                window.setVerticalSyncEnabled(true);
            buttons[1]->changeButtonName("Windowed");
            *fullscreen = false;
        }
        else
        {
            window.close();
            window.create(sf::VideoMode(1280, 720), "Shootan", sf::Style::Fullscreen);
            if (*verticalSync)
                window.setVerticalSyncEnabled(true);
            buttons[1]->changeButtonName("Fullscreen");
            *fullscreen = true;
        }
        break;
    case 5:
        /*if(window.getSize().x == 1280)
        {
            window.close();
            window.create(sf::VideoMode(1920, 1080), "Shootan");
            if (*verticalSync)
                window.setVerticalSyncEnabled(true);
        }
        else
        {
            window.close();
            window.create(sf::VideoMode(1280, 720), "Shootan");
            if (*verticalSync)
                window.setVerticalSyncEnabled(true);
        } */
        break;
    case 6:
        backToMainMenu();
        break;
    default:
        break;
    }
}

void MainMenu::createSettingsMenu()
{
    string str[5];
    isSettings = true;
    str[0] = "Vertical Sync";
    if (*fullscreen)
        str[1] = "Fullscreen";
    else
        str[1] = "Windowed";
    if (window.getSize().x == 1280)
        str[2] = "720";
    if (window.getSize().x == 1920)
        str[2] = "1080";
    str[3] = "Back";
    str[4] = "./data/interface/button4.png";
    buttons.clear();
    buttons.push_back(new CheckBox(str[0],28.f,window.getSize().x / 2,window.getSize().y / 2 - 176,3,verticalSync));
    for(int i = 1; i < 4; i++)
        buttons.push_back(new Button(str[i],str[4],30.f,window.getSize().x / 2,window.getSize().y / 2 - 176 + i*116,i+3));
    for(int i = 0; i < 5; i++)
    str[i].erase();
}

void MainMenu::backToMainMenu()
{
    isSettings = false;
    string str[4];
    str[0] = "Play";
    str[1] = "Settings";
    str[2] = "Exit";
    str[3] = "./data/interface/button.png";
    buttons.clear();
    for(int i = 0; i < 3; i++)
        buttons.push_back(new Button(str[i],str[3],30.f,window.getSize().x / 2,window.getSize().y / 2 - 150 + i*150,i));
    for(int i = 0; i < 4; i++)
        str[i].erase();
}
void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
