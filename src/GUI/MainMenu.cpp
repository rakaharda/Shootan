#include "GUI/MainMenu.h"
#include <iostream>
MainMenu::MainMenu(GameStates *_gameState, MenuStates *_menuState)
{
    setFunctions();
    loadResources();
    gameState = _gameState;
    menuState = _menuState;
    m_isCaption = false;
    *menuState = MenuStates::MS_MAIN_MENU;
    string buttonName[4];
    buttonName[0] = "buttonMainPlay";
    buttonName[1] = "buttonMainSettings";
    buttonName[2] = "buttonMainCredits";
    buttonName[3] = "buttonMainExit";
    captionSprite.setTexture(resources->getTexture("caption"));
    captionSprite.setPosition(window.getSize().x / 2 - captionSprite.getTexture()->getSize().x / 2, window.getSize().y);
    backgroundCaption.setTexture(resources->getTexture("background_caption"));
    int bgHight = backgroundCaption.getTexture()->getSize().y / 2 - window.getSize().y / 2;
    backgroundCaption.setPosition(window.getSize().x / 2 - backgroundCaption.getTexture()->getSize().x / 2, -bgHight);
    backGroundSprite.setTexture(resources->getTexture("backgroundMainMenu"));
    backGroundSprite.setPosition(window.getSize().x / 2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y / 2 - backGroundSprite.getTexture()->getSize().y / 2);
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
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape && isCaption())
            stopCaption();
        break;
    case sf::Event::MouseButtonPressed:
        if(!isCaption())
            switch(event.mouseButton.button)
            {
            case sf::Mouse::Left:
                searchButton();
                break;
            default:
                break;
            }
            break;
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
    buttonFunctions[2] = [this](){
        caption();
        resources->getMusic("GXRCH - HARD")->setVolume(audioSettings->music);
        resources->getMusic("GXRCH - HARD")->play();
    };
    buttonFunctions[3] = [this](){
        *gameState = GameStates::GS_ENDGAME;
    };
}

void MainMenu::playCaption()
{
    if(-captionSprite.getPosition().y > captionSprite.getTexture()->getSize().y)
        stopCaption();
    captionSprite.move(0,-40*frameTime);
}

void MainMenu::stopCaption()
{
    uncaption();
    resources->getMusic("GXRCH - HARD")->pause();
    captionSprite.setPosition(window.getSize().x / 2 - captionSprite.getTexture()->getSize().x / 2, window.getSize().y);
}

void MainMenu::loadResources()
{
    resources->addTexture("buttonMainPlay",         "./data/GUI/MainMenu/buttonMainPlay.png");
    resources->addTexture("buttonMainSettings",     "./data/GUI/MainMenu/buttonMainSettings.png");
    resources->addTexture("buttonMainCredits",      "./data/GUI/MainMenu/buttonMainCredits.png");
    resources->addTexture("buttonMainExit",         "./data/GUI/MainMenu/buttonMainExit.png");
    resources->addTexture("buttonMainPlayLight",    "./data/GUI/MainMenu/buttonMainPlayLight.png");
    resources->addTexture("buttonMainSettingsLight","./data/GUI/MainMenu/buttonMainSettingsLight.png");
    resources->addTexture("buttonMainCreditsLight", "./data/GUI/MainMenu/buttonMainCreditsLight.png");
    resources->addTexture("buttonMainExitLight",    "./data/GUI/MainMenu/buttonMainExitLight.png");
    resources->addTexture("backgroundMainMenu",     "./data/GUI/MainMenu/backgroundMainMenu.png");
    resources->addTexture("caption",                "./data/GUI/MainMenu/caption.png");
    resources->addTexture("background_caption",     "./data/GUI/MainMenu/backgroundCaption.png");
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_isCaption)
    {
        target.draw(backgroundCaption,states);
        target.draw(captionSprite,states);
        return;
    }
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}

bool MainMenu::isCaption()
{
    return m_isCaption;
}

void MainMenu::caption()
{
    m_isCaption = true;
}

void MainMenu::uncaption()
{
    m_isCaption = false;
}
