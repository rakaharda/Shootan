#include "GUI/MainMenu.h"
#include <iostream>
MainMenu::MainMenu(GameStates *_gameState, MenuStates *_menuState)
{
    setFunctions();
    loadResources();
    gameState = _gameState;
    menuState = _menuState;
    *menuState = MenuStates::MS_MAIN_MENU;
    string buttonName[4];
    buttonName[0] = "buttonMainPlay";
    buttonName[1] = "buttonMainSettings";
    buttonName[2] = "buttonMainCredits";
    buttonName[3] = "buttonMainExit";
    backGroundSprite.setTexture(resources->getTexture("backgroundMainMenu"));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);
    for(unsigned int i = 0; i < 4; i++){
        buttons.push_back(new Button(resources->getTexture(buttonName[i]),window.getSize().x/2,window.getSize().y/2 - 180 + i*120));
        buttons.back()->setFunction(buttonFunctions[i]);
        buttons.back()->setLightButton(buttonName[i]+"Light");
    }
}

MainMenu::~MainMenu()
{
    resources->deleteTexture("buttonMainPlay");
    resources->deleteTexture("buttonMainSettings");
    resources->deleteTexture("buttonMainCredits");
    resources->deleteTexture("buttonMainExit");
}

void MainMenu::handleEvents(sf::Event event)
{

    for(unsigned int i = 0; i < buttons.size(); i++)
        buttons[i]->update();
    switch(event.type)
    {
    case sf::Event::MouseButtonPressed:
        switch(event.mouseButton.button)
        {
        case sf::Mouse::Left:
            searchButton();
            break;
        default:
            break;
        }
    default:
        break;
    }
}
void MainMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [10];
    buttonFunctions[0] = [this](){
        *gameState = GameStates::GS_GAMEMODE_SURVIVAL;
    };
    buttonFunctions[1] = [this](){
        *menuState = MenuStates::MS_CREATE_SETTINGS_MENU;
    };
    buttonFunctions[2] = [](){};
    buttonFunctions[3] = [](){
        //*isPlaying = false;
        window.close();
    };
}


void MainMenu::loadResources()
{
    resources->addTexture("buttonMainPlay","./data/GUI/MainMenu/buttonMainPlay.png");
    resources->addTexture("buttonMainSettings","./data/GUI/MainMenu/buttonMainSettings.png");
    resources->addTexture("buttonMainCredits","./data/GUI/MainMenu/buttonMainCredits.png");
    resources->addTexture("buttonMainExit","./data/GUI/MainMenu/buttonMainExit.png");
    resources->addTexture("buttonMainPlayLight","./data/GUI/MainMenu/buttonMainPlayLight.png");
    resources->addTexture("buttonMainSettingsLight","./data/GUI/MainMenu/buttonMainSettingsLight.png");
    resources->addTexture("buttonMainCreditsLight","./data/GUI/MainMenu/buttonMainCreditsLight.png");
    resources->addTexture("buttonMainExitLight","./data/GUI/MainMenu/buttonMainExitLight.png");
    resources->addTexture("backgroundMainMenu","./data/GUI/MainMenu/backgroundMainMenu.png");
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
