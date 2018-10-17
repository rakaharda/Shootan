#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"

class MainMenu: public Menu
{
    public:
        MainMenu(bool *_menuStatus);
        virtual ~MainMenu();
    private:
        void startProcess(int _id);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;


#endif // MAINMENU_H
