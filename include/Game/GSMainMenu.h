#ifndef GSMAINMENU_H
#define GSMAINMENU_H

#include "GUI/MainMenu.h"
#include "GUI/SettingsMenu.h"
#include "Components/GameStates.h"
#include "Game/GameState.h"

class GSMainMenu: public GameState
{
public:
    GSMainMenu(VideoSettings *_videoSettings);
    virtual ~GSMainMenu();
    GameStates update();
    void draw();
    void handleEvents(sf::Event _event);
private:
    bool isSettings;
    void loadresources();
    GameStates gameState;
    VideoSettings *videoSettings;
    MainMenu *mainMenu;
    SettingsMenu *settingsMenu;
    sf::Sprite background;
};

extern sf::RenderWindow     window;
extern ResourceManager *resources;

#endif // GSMAINMENU_H
