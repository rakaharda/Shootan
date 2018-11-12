#include "GUI/MainMenu.h"
#include <iostream>
MainMenu::MainMenu(GameStates *_gameState, bool *_isSettings)
{
    setFunctions();
    loadResources();
    isSettings = _isSettings;
    gameState = _gameState;
    string buttonName[4];
    buttonName[0] = "buttonMainPlay";
    buttonName[1] = "buttonMainSettings";
    buttonName[2] = "buttonMainCredits";
    buttonName[3] = "buttonMainExit";
    backGroundSprite.setTexture(resources->getTexture("backgroundMainMenu"));
    backGroundSprite.setColor(sf::Color(255,255,255,85));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);
    for(unsigned int i = 0; i < 4; i++){
        buttons.push_back(new Button(resources->getTexture(buttonName[i]),window.getSize().x/2,window.getSize().y/2 - 240 + i*160));
        buttons.back()->setFunction(buttonFunctions[i]);
        buttonName[i].erase();
    }
}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::handleEvents(sf::Event event)
{

    /*if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        slider->isPressed(sf::Mouse::getPosition(window).x,
                sf::Mouse::getPosition(window).y);
    else slider->pressed = false; */
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
        *isSettings = true;
    };
    buttonFunctions[2] = [](){};
    buttonFunctions[3] = [this](){
        //*isPlaying = false;
    };
}


void MainMenu::loadResources()
{
    resources->addTexture("buttonMainPlay","./data/GUI/MainMenu/buttonMainPlay.png");
    resources->addTexture("buttonMainSettings","./data/GUI/MainMenu/buttonMainSettings.png");
    resources->addTexture("buttonMainCredits","./data/GUI/MainMenu/buttonMainCredits.png");
    resources->addTexture("buttonMainExit","./data/GUI/MainMenu/buttonMainExit.png");
    resources->addTexture("backgroundMainMenu","./data/GUI/MainMenu/backgroundMainMenu.png");
    resources->addTexture("sliderLine", "./data/GUI/mainSettingsMenu/sliderLineMainSettingsMenu.png");
    resources->addTexture("sliderButton", "./data/GUI/mainSettingsMenu/sliderMainSettingsMenu.png");
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
