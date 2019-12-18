#include "GUI/MultiplayerMenu.h"
#include <iostream>

MultiplayerMenu::MultiplayerMenu(GameStates *_gameState, MenuStates *_menuState, int *_mode)
{
    ip = sf::IpAddress::getLocalAddress();
    gameState = _gameState;
    menuState = _menuState;
    mode = _mode;
    loadResources();
    setButtons();
    setFunctions();
    *menuState = MenuStates::MS_MULTIPLAYER_MENU;
    multiplayerState = MultiplayerStates::MPS_SELECT_MODE;
    backGroundSprite.setTexture(resources->getTexture("backgroundMultiplayerMenu"));
    backGroundSprite.setPosition(window.getSize().x / 2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y / 2 - backGroundSprite.getTexture()->getSize().y / 2);
}

MultiplayerMenu::~MultiplayerMenu()
{

}

void MultiplayerMenu::handleEvents(sf::Event event)
{
    int i, n;
    switch (multiplayerState)
    {
    case MultiplayerStates::MPS_SELECT_MODE:
        for(auto &i : buttons)
            i->handleEvents(event);
        break;
    case MultiplayerStates::MPS_ENTER_IP:
        for(auto &i : enterButtons)
            i->handleEvents(event);;
        textBoxes[0]->handleEvents(event);
    case MultiplayerStates::MPS_LOBBY:
        for(auto &i : lobbyButtons)
            i->handleEvents(event);;
    default:
        break;
    }

}

void MultiplayerMenu::update()
{
    if(multiplayerState == MultiplayerStates::MPS_ENTER_IP)
    {
        textBoxes[0]->update();
    }
}

void MultiplayerMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [10];
    buttonFunctions[0] = [this]()
    {
        *mode = 0;
        multiplayerState = MultiplayerStates::MPS_LOBBY;
    };
    buttons[0]->setFunction(buttonFunctions[0]);
    buttonFunctions[1] = [this]()
    {
        *mode = 1;
        multiplayerState = MultiplayerStates::MPS_ENTER_IP;
    };
    buttons[1]->setFunction(buttonFunctions[1]);
    buttonFunctions[2] = [this]()
    {
        multiplayerState = MultiplayerStates::MPS_LOBBY;
    };
    enterButtons[0]->setFunction(buttonFunctions[3]);
    buttonFunctions[3] = [this]()
    {
        *gameState = GameStates::GS_GAMEMODE_PVP;
    };
    lobbyButtons[0]->setFunction(buttonFunctions[4]);
    buttonFunctions[4] = [this]()
    {
        *menuState = MenuStates::MS_CREATE_MAIN_MENU;
    };
    buttons.back()->setFunction(buttonFunctions[4]);
}


void MultiplayerMenu::loadResources()
{
    resources->addTexture("buttonSelectHost",         "./data/GUI/MultiplayerMenu/buttonSelectHost.png");
    resources->addTexture("buttonSelectClient",       "./data/GUI/MultiplayerMenu/buttonSelectClient.png");
    resources->addTexture("backgroundMultiplayerMenu","./data/GUI/MultiplayerMenu/backgroundMultiplayerMenu.png");
    resources->addTexture("buttonMultiplayerBack",    "./data/GUI/MultiplayerMenu/buttonMultiplayerBack.png");
    resources->addTexture("buttonSubmit",             "./data/GUI/MultiplayerMenu/buttonSubmit.png");
    resources->addTexture("textBoxDefault",           "./data/GUI/MultiplayerMenu/textBoxDefault.png");
    resources->addTexture("cursorDefault",            "./data/GUI/MultiplayerMenu/cursorDefault.png");
    resources->addTexture("buttonMultiplayerPlay",    "./data/GUI/MultiplayerMenu/buttonMultiplayerPlay.png");
    resources->addTexture("labelEnterIp",             "./data/GUI/MultiplayerMenu/labelEnterIp.png");
    resources->addTexture("labelSelectMode",          "./data/GUI/MultiplayerMenu/labelSelectMode.png");
    resources->addFont("Mylodon-Light",               "./data/fonts/Mylodon-Light.otf");
}

void MultiplayerMenu::setButtons()
{
    Button* back = new Button(resources->getTexture("buttonMultiplayerBack"), window.getSize().x/2 - 150, window.getSize().y/2 + 150);
    buttons.push_back(new Button(resources->getTexture("buttonSelectHost"), window.getSize().x/2, window.getSize().y/2 - 80));
    buttons.push_back(new Button(resources->getTexture("buttonSelectClient"), window.getSize().x/2, window.getSize().y/2 + 20));
    buttons.push_back(back);
    enterButtons.push_back(new Button(resources->getTexture("buttonSubmit"), window.getSize().x/2, window.getSize().y/2 + 20));
    enterButtons.push_back(back);
    lobbyButtons.push_back(new Button(resources->getTexture("buttonMultiplayerPlay"), window.getSize().x/2 + 150, window.getSize().y/2 + 150));
    lobbyButtons.push_back(back);

    textBoxes.push_back(new TextBox("", window.getSize().x/2, window.getSize().y/2 - 80));
    textBoxes[0]->setFunction([](){});

    labeles.push_back(new sf::Sprite(resources->getTexture("labelSelectMode")));
    labeles.back()->setPosition(window.getSize().x/2 - resources->getTexture("labelSelectMode").getSize().x / 2,
                                window.getSize().y/2 - resources->getTexture("labelSelectMode").getSize().x / 2 - 60);
    labeles.push_back(new sf::Sprite(resources->getTexture("labelEnterIp")));
    labeles.back()->setPosition(window.getSize().x/2 - resources->getTexture("labelEnterIp").getSize().x / 2,
                                window.getSize().y/2 - resources->getTexture("labelEnterIp").getSize().x / 2 - 60);

    textIp.setCharacterSize(30);
    textIp.setFillColor(sf::Color(60, 180, 240));
    textIp.setFont(resources->getFont("Mylodon-Light"));
    textIp.setString("Your Ip: " + ip.toString());
    auto bounds = textIp.getGlobalBounds();
    textIp.setPosition(window.getSize().x/2 - bounds.width / 2,
                       window.getSize().y/2 - bounds.height / 2 - 150);
}

void MultiplayerMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    int i, n;
    switch (multiplayerState)
    {
    case MultiplayerStates::MPS_SELECT_MODE:
        for(auto &i : buttons)
            target.draw(*i, states);
        target.draw(*labeles[0], states);
        break;
    case MultiplayerStates::MPS_ENTER_IP:
        for(auto &i : enterButtons)
            target.draw(*i, states);
        target.draw(*labeles[1], states);
        target.draw(*textBoxes[0], states);
        break;
    case MultiplayerStates::MPS_LOBBY:
        for(auto &i : lobbyButtons)
            target.draw(*i, states);
        target.draw(textIp, states);
        break;
    default:
        break;
    }
}
