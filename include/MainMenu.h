#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include "CheckBox.h"

class MainMenu: public Menu
{
    public:
        MainMenu(bool *_menuStatus, bool *_fullscreen, bool *_verticalSync);
        bool *fullscreen;
        bool *verticalSync; 
        virtual ~MainMenu();
    private:
        void startProcess(int _id);
        void createSettingsMenu();
        void backToMainMenu();
        bool isSettings;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;


#endif // MAINMENU_H
