#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include "GUI/CheckBox.h"

class MainMenu: public Menu
{
public:
    MainMenu(bool *_menuStatus, bool *_fullscreen, bool *_verticalSync, sf::Sprite& _playerSprite);
    bool *fullscreen;
    bool *verticalSync;
    virtual ~MainMenu();
private:
    void startProcess(int _id);
    void createSettingsMenu();
    void backToMainMenu();
    void refreshMenu();
    bool isSettings;
    std::function<void(void)> buttonFunctions[2];
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;


#endif // MAINMENU_H
