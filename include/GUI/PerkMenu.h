#ifndef PERKMENU_H
#define PERKMENU_H

#include "Menu.h"
#include "Game/VideoSettings.h"
#include "Player/Player.h"

class PerkMenu: public Menu
{
public:
    PerkMenu(bool *_menuStatus, Player** _player);
    virtual ~PerkMenu();
    void handleEvents(sf::Event event);
private:
    int maxHP;
    int currentHP;
    int maxSpeed;
    int currentSpeed;
    Player* player;
    void setFunctions();
friend Button;
//    buttonFunctions;
};

extern sf::RenderWindow window;


#endif // PERKMENU_H
