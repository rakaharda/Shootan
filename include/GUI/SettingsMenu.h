#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "GUI/Menu.h"
#include "Game/VideoSettings.h"
#include "Utils/ResourceManager.h"
#include "GUI/Checkbox.h"

class SettingsMenu: public Menu
{
public:
    SettingsMenu(VideoSettings *_videoSettings, bool *_isSettings);
    virtual ~SettingsMenu();
private:
    VideoSettings tempVideoSettings;
    VideoSettings *videoSettings;
    void setFunctions();
    void loadResources();
    void refreshMenu();
    bool *isSettings;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;
extern ResourceManager *resources;

#endif // SETTINGSMENU_H
