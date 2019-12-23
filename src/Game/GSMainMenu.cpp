#include "Game/GSMainMenu.h"
#include <iostream>
GSMainMenu::GSMainMenu(VideoSettings *_videoSettings)
{
    videoSettings = _videoSettings;
    gameState = GameStates::GS_MAINMENU;
    menuState = new MenuStates;
    *menuState = MenuStates::MS_CREATE_MAIN_MENU;
    loadresources();
    backgroundSize = videoSettings->height;
    background.setTexture(resources->getTexture("mainBackground"));
    background.setScale((float)videoSettings->width/background.getTexture()->getSize().x,
                        (float)videoSettings->height/background.getTexture()->getSize().y); 
}

GSMainMenu::~GSMainMenu()
{
    delete(mainMenu);

}

void GSMainMenu::handleEvents(sf::Event event)
{
    switch(*menuState)
    {
    case MenuStates::MS_MAIN_MENU:
        mainMenu->handleEvents(event);
        break;
    case MenuStates::MS_SETTINGS_MENU:
        settingsMenu->handleEvents(event);
        break;
    case MenuStates::MS_MULTIPLAYER_MENU:
        multiplayerMenu->handleEvents(event);
        break;
    default:
        break;
    }
}

GameStates GSMainMenu::update()
{
    switch(*menuState)
    {
    case MenuStates::MS_CREATE_MAIN_MENU:
        mainMenu = new MainMenu(&gameState, menuState);
        break;
    case MenuStates::MS_CREATE_SETTINGS_MENU:
        settingsMenu = new SettingsMenu(videoSettings, menuState);
        break;
    case MenuStates::MS_CREATE_MULTIPLAYER_MENU:
        multiplayerMenu = new MultiplayerMenu(&gameState, menuState, videoSettings);
        cout << "3" << endl;
        break;
    case MenuStates::MS_MAIN_MENU:
        if(mainMenu->isCaption())
            mainMenu->playCaption();
        break;
    case MenuStates::MS_MULTIPLAYER_MENU:
        multiplayerMenu->update();
        break;
    default:
        break;
    }
    if(backgroundSize != videoSettings->height)
    {
         background.setScale((float)videoSettings->width/background.getTexture()->getSize().x,
                             (float)videoSettings->height/background.getTexture()->getSize().y);
        backgroundSize = videoSettings->height;
    }
    return gameState;
}

void GSMainMenu::loadresources()
{
    resources->addTexture("mainBackground",    "./data/GUI/MainMenu/mainBackground.png");
    resources->addMusic("GXRCH - HARD",        "./data/music/act.ogg");
    resources->addMusic("GXRCH - HARD(intro)", "./data/music/sim.ogg");
}

void GSMainMenu::draw()
{
    window.draw(background);
    switch(*menuState)
    {
    case MenuStates::MS_MAIN_MENU:
         window.draw(*mainMenu);
        break;
    case MenuStates::MS_SETTINGS_MENU:
         window.draw(*settingsMenu);
        break;
    case MenuStates::MS_MULTIPLAYER_MENU:
        window.draw(*multiplayerMenu);
    default:
        break;
    }
}
