#include "GUI/GameOverMenu.h"

GameOverMenu::GameOverMenu()
{
    gameState = GameStates::GS_GAMEMODE_SURVIVAL;
    setFunctions();
    loadResources();
    string buttonName[2];
    buttonName[0] = "buttonRestart";
    buttonName[1] = "buttonToMainMenu";
    for(int i = 0; i < 2; i++){
        buttons.push_back(new Button(resources->getTexture(buttonName[i]),window.getSize().x/2,window.getSize().y/2 - 100 + i*200));
        buttons.back()->setFunction(buttonFunctions[i]);
        buttons.back()->setLightButton(buttonName[i]+"Light");
    }
    backGroundSprite.setTexture(resources->getTexture("backgroundGameOverMenu"));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);
}

GameOverMenu::~GameOverMenu()
{
    //dtor
}

void GameOverMenu::loadResources()
{
    resources->addTexture("buttonRestart",     "./data/GUI/gameOverMenu/buttonRestart.png");
    resources->addTexture("buttonToMainMenu",     "./data/GUI/gameOverMenu/buttonToMainMenu.png");
    resources->addTexture("buttonRestartLight",     "./data/GUI/gameOverMenu/buttonRestartLight.png");
    resources->addTexture("buttonToMainMenuLight",     "./data/GUI/gameOverMenu/buttonToMainMenuLight.png");
    resources->addTexture("backgroundGameOverMenu",     "./data/GUI/gameOverMenu/background.png");
}

void GameOverMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [2];
    buttonFunctions[0] = [this](){

    };

    buttonFunctions[1] = [this](){
        gameState = GameStates::GS_MAINMENU;
    };
}

void GameOverMenu::handleEvents(sf::Event event)
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
        break;
    default:
        break;
    }
}

void GameOverMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
