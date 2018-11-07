#include "GUI/PerkMenu.h"

PerkMenu::PerkMenu(bool *_menuStatus, Player** _player)
{
    maxHP=5;
    currentHP=0;
    maxSpeed=5;
    currentSpeed=0;
    player=*_player;
    menuStatus = _menuStatus;
    setFunctions();
    string str[4];
    str[0] = "Play";
    str[1] = "+HP";
    str[2] = "+SPEED";
    str[3] = "./data/interface/button3.png";
    for(int i = 0; i < 3; i++)
        buttons.push_back(new Button(str[i], str[3], 30.f, window.getSize().x/2, window.getSize().y/2 - 150 + i*150, buttonFunctions[i]));
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
        //HP++
        if(currentHP<maxHP)
        {
            currentHP++;
            player->setHealthPoints(player->getHealthPoints() + 50);
            player->setCurrentHealthPoints(player->getHealthPoints());
        }
    };
    buttonFunctions[2] = [this](){
        //Perk UpSpeed++
        if(currentSpeed<maxSpeed)
        {
            currentSpeed++;
            if(player->speed != 200.f)
            {
                player->speed -= player->upSpeed;
                player->upSpeed += 50.f;
                player->speed += player->upSpeed;
            }
            else
            player->upSpeed += 50.f;
        }
    };
}
