#ifndef MAINMENU_H
#define MAINMENU_H

#include "Menu.h"
#include "GUI/CheckBox.h"
#include "Game/VideoSettings.h"

class MainMenu: public Menu
{
public:
    MainMenu(VideoSettings *_videoSettings, bool *_menuStatus);
    virtual ~MainMenu();
private:
    void refreshMenu();
    void setFunctions();
    bool isSettings;
    bool *isPlaying;
    VideoSettings *videoSettings;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
friend Button;
//    buttonFunctions;
};

extern sf::RenderWindow window;


#endif // MAINMENU_H
