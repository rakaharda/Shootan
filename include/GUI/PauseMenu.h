#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"
#include "GUI/CheckBox.h"
#include "Game/VideoSettings.h"
#include "Utils/ResourceManager.h"

class PauseMenu: public Menu
{
public:
    PauseMenu(VideoSettings *_videoSettings, bool *_menuStatus);
    virtual ~PauseMenu();
private:
    void refreshMenu();
    void setFunctions();
    void loadResources();
    bool isSettings;
    bool *isPlaying;
    VideoSettings tempVideoSettings;
    VideoSettings *videoSettings;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
friend Button;
//    buttonFunctions;
};

extern sf::RenderWindow window;
extern ResourceManager      *resources;

#endif // PAUSEMENU_H
