#include "GUI/PerkMenu.h"

PerkMenu::PerkMenu(bool *_menuStatus)
{
    menuStatus = _menuStatus;
    setFunctions();
    string str[4];
    str[0] = "Play";
    str[1] = "+HP";
    str[2] = "+SPEED";
    str[3] = "./data/interface/button3.png";
    for(int i = 0; i < 3; i++)
        buttons.push_back(new Button(str[i],str[3],30.f,window.getSize().x/2,window.getSize().y/2 - 150 + i*150, buttonFunctions[i]));
    for(int i = 0; i < 4; i++)
        str[i].erase();
    backGroundTexture.loadFromFile("./data/interface/background.png");
    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);

}

PerkMenu::~PerkMenu()
{
    //dtor
}

void PerkMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [3];
    buttonFunctions[0] = [this](){
        *menuStatus = false;
    };
    buttonFunctions[1] = [this](){
        *menuStatus = false;
    };
    buttonFunctions[2] = [this](){
        *menuStatus = false;
    };
}
