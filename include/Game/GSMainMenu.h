#ifndef GSMAINMENU_H
#define GSMAINMENU_H

#include "GUI/MainMenu.h"
#include "GUI/SettingsMenu.h"
#include "GUI/MultiplayerMenu.h"
#include "GUI/MenuStates.h"
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
    void loadresources();
    int backgroundSize;
    int mode;
    GameStates gameState;
    MenuStates *menuState;
    VideoSettings *videoSettings;
    MainMenu *mainMenu;
    MultiplayerMenu *multiplayerMenu;
    SettingsMenu *settingsMenu;
    sf::Sprite background;
};

extern sf::RenderWindow     window;
extern ResourceManager *resources;

#endif // GSMAINMENU_H
