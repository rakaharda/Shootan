#include "Game/GSMainMenu.h"
#include <iostream>
GSMainMenu::GSMainMenu(VideoSettings *_videoSettings)
{
    videoSettings = _videoSettings;
    gameState = GameStates::GS_MAINMENU;
    menuState = new MenuStates;
    *menuState = MenuStates::MS_CREATE_MAIN_MENU;
    loadresources();
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
    default:
        break;
    }
    return gameState;
}

void GSMainMenu::loadresources()
{
    resources->addTexture("mainBackground", "./data/GUI/MainMenu/mainBackground.png");
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
    default:
        break;
    }
}
