#ifndef PERKMENU_H
#define PERKMENU_H

#include "Menu.h"
#include "Game/VideoSettings.h"
#include "Player/Player.h"

class PerkMenu: public Menu
{
public:
    PerkMenu(bool *_menuStatus);
    virtual ~PerkMenu();
    static Player* player;
private:
    void setFunctions();
friend Button;
//    buttonFunctions;
};

extern sf::RenderWindow window;


#endif // PERKMENU_H
