#include "GUI/MultiplayerMenu.h"
#include <iostream>

MultiplayerMenu::MultiplayerMenu(GameStates *_gameState, MenuStates *_menuState, VideoSettings *_videoSettings)
{
    ip = sf::IpAddress::getLocalAddress();
    gameState = _gameState;
    menuState = _menuState;
    connected = false;
    videoSettings = _videoSettings;
    loadResources();
    setButtons();
    setFunctions();
    *menuState = MenuStates::MS_MULTIPLAYER_MENU;
    mpMenuState = MultiplayerMenuStates::MPMS_SELECT_MODE;
    backGroundSprite.setTexture(resources->getTexture("backgroundMultiplayerMenu"));
    backGroundSprite.setPosition(window.getSize().x / 2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y / 2 - backGroundSprite.getTexture()->getSize().y / 2);
}

MultiplayerMenu::~MultiplayerMenu()
{

}

void MultiplayerMenu::handleEvents(sf::Event event)
{
    switch (mpMenuState)
    {
    case MultiplayerMenuStates::MPMS_SELECT_MODE:
        for(auto &i : buttons)
            i->handleEvents(event);
        break;
    case MultiplayerMenuStates::MPMS_ENTER_IP:
        for(auto &i : enterButtons)
            i->handleEvents(event);
        textBoxes[0]->handleEvents(event);
        break;
    case MultiplayerMenuStates::MPMS_LOBBY:
        if(multiplayerState->getSate() == MultiplayerStates::MPS_MENU_WAITING)
            lobbyButtons[0]->handleEvents(event);
        for(int i = 1; i < lobbyButtons.size(); i++)
            lobbyButtons[i]->handleEvents(event);
        break;
    default:
        break;
    }

}

void MultiplayerMenu::update()
{
    if(mpMenuState == MultiplayerMenuStates::MPMS_SELECT_MODE)
    {
        for(auto &i : buttons)
        {
            i->update();
        }
    }
    else if(mpMenuState == MultiplayerMenuStates::MPMS_ENTER_IP)
    {
        textBoxes[0]->update();
        for(auto &i : enterButtons)
        {
            i->update();
        }
    }
    else if(mpMenuState == MultiplayerMenuStates::MPMS_LOBBY)
    {
        if(!connected)
        {
            if(multiplayerState->getSate() == MultiplayerStates::MPS_MENU_CONNECTING)
            {
                multiplayerState->update();
                if(clock.getElapsedTime().asSeconds() > 2.f)
                {
                    labeles[2]->setTextureRect(sf::IntRect(0, 0, labeles[2]->getTexture()->getSize().x, labeles[2]->getTexture()->getSize().y));
                    clock.restart();
                }
                else if(clock.getElapsedTime().asSeconds() > 1.5)
                {
                    labeles[2]->setTextureRect(sf::IntRect(0, 0, labeles[2]->getTexture()->getSize().x - 20, labeles[2]->getTexture()->getSize().y));
                }
                else if(clock.getElapsedTime().asSeconds() > 1.f)
                {
                    labeles[2]->setTextureRect(sf::IntRect(0, 0, labeles[2]->getTexture()->getSize().x - 40, labeles[2]->getTexture()->getSize().y));
                }
                else if(clock.getElapsedTime().asSeconds() > 0.5)
                {
                    labeles[2]->setTextureRect(sf::IntRect(0, 0, labeles[2]->getTexture()->getSize().x - 60, labeles[2]->getTexture()->getSize().y));
                }

            }
            else
            {
                connected = true;
                lobbyButtons[0]->setLightButton("buttonMultiplayerPlayLight");
            }

        }
        for(auto &i : lobbyButtons)
        {
            i->update();
        }
    }
}

void MultiplayerMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [10];
    buttonFunctions[0] = [this]()
    {
        mode = 1;
        mpMenuState = MultiplayerMenuStates::MPMS_LOBBY;
        multiplayerState = new GSMPHost(videoSettings);

    };
    buttons[0]->setFunction(buttonFunctions[0]);
    buttonFunctions[1] = [this]()
    {
        mode = 2;
        mpMenuState = MultiplayerMenuStates::MPMS_ENTER_IP;
    };
    buttons[1]->setFunction(buttonFunctions[1]);
    buttonFunctions[2] = [this]()
    {
        mpMenuState = MultiplayerMenuStates::MPMS_LOBBY;
        multiplayerState = new GSMPClient(videoSettings, textBoxes[0]->getText());
    };
    textBoxes[0]->setFunction(buttonFunctions[2]);
    enterButtons[0]->setFunction(buttonFunctions[2]);
    buttonFunctions[3] = [this]()
    {
        if(mode == 1)
            *gameState = GameStates::GS_GAMEMODE_MPHOST;
        else if(mode == 2)
            *gameState = GameStates::GS_GAMEMODE_MPCLIENT;
        multiplayerState->setState(MPS_PLAY);
    };
    lobbyButtons[0]->setFunction(buttonFunctions[3]);
    buttonFunctions[4] = [this]()
    {
        *menuState = MenuStates::MS_CREATE_MAIN_MENU;
        cout << "da\n";
    };
    buttons.back()->setFunction(buttonFunctions[4]);
}


void MultiplayerMenu::loadResources()
{
    resources->addTexture("buttonSelectHost",         "./data/GUI/MultiplayerMenu/buttonSelectHost.png");
    resources->addTexture("buttonSelectHostLight",         "./data/GUI/MultiplayerMenu/buttonSelectHostLight.png");
    resources->addTexture("buttonSelectClient",       "./data/GUI/MultiplayerMenu/buttonSelectClient.png");
    resources->addTexture("buttonSelectClientLight",       "./data/GUI/MultiplayerMenu/buttonSelectClientLight.png");
    resources->addTexture("backgroundMultiplayerMenu","./data/GUI/MultiplayerMenu/backgroundMultiplayerMenu.png");
    resources->addTexture("buttonMultiplayerBack",    "./data/GUI/MultiplayerMenu/buttonMultiplayerBack.png");
    resources->addTexture("buttonMultiplayerBackLight",    "./data/GUI/MultiplayerMenu/buttonMultiplayerBackLight.png");
    resources->addTexture("buttonSubmit",             "./data/GUI/MultiplayerMenu/buttonSubmit.png");
    resources->addTexture("buttonSubmitLight",             "./data/GUI/MultiplayerMenu/buttonSubmitLight.png");
    resources->addTexture("textBoxDefault",           "./data/GUI/MultiplayerMenu/textBoxDefault.png");
    resources->addTexture("cursorDefault",            "./data/GUI/MultiplayerMenu/cursorDefault.png");
    resources->addTexture("buttonMultiplayerPlay",    "./data/GUI/MultiplayerMenu/buttonMultiplayerPlay.png");
    resources->addTexture("buttonMultiplayerPlayLight",    "./data/GUI/MultiplayerMenu/buttonMultiplayerPlayLight.png");
    resources->addTexture("labelEnterIp",             "./data/GUI/MultiplayerMenu/labelEnterIp.png");
    resources->addTexture("labelSelectMode",          "./data/GUI/MultiplayerMenu/labelSelectMode.png");
    resources->addTexture("labelConnecting",          "./data/GUI/MultiplayerMenu/labelConnecting.png");
    resources->addTexture("labelConnected",          "./data/GUI/MultiplayerMenu/labelConnected.png");
    resources->addFont("Mylodon-Light",               "./data/fonts/Mylodon-Light.otf");
}

void MultiplayerMenu::setButtons()
{
    Button* back = new Button(resources->getTexture("buttonMultiplayerBack"), window.getSize().x/2 - 235, window.getSize().y/2 + 140);
    back->setLightButton("buttonMultiplayerBackLight");
    buttons.push_back(new Button(resources->getTexture("buttonSelectHost"), window.getSize().x/2 - 160, window.getSize().y/2 - 20));
    buttons.back()->setLightButton("buttonSelectHostLight");
    buttons.push_back(new Button(resources->getTexture("buttonSelectClient"), window.getSize().x/2 + 160, window.getSize().y/2 - 20));
    buttons.back()->setLightButton("buttonSelectClientLight");
    buttons.push_back(back);
    enterButtons.push_back(new Button(resources->getTexture("buttonSubmit"), window.getSize().x/2, window.getSize().y/2 + 20));
    enterButtons.back()->setLightButton("buttonSubmitLight");
    enterButtons.push_back(back);
    lobbyButtons.push_back(new Button(resources->getTexture("buttonMultiplayerPlay"), window.getSize().x/2 + 235, window.getSize().y/2 + 140));
    lobbyButtons.push_back(back);

    textBoxes.push_back(new TextBox("", window.getSize().x/2, window.getSize().y/2 - 80));

    labeles.push_back(new sf::Sprite(resources->getTexture("labelSelectMode")));
    labeles.back()->setPosition(window.getSize().x/2 - resources->getTexture("labelSelectMode").getSize().x / 2,
                                window.getSize().y/2 - resources->getTexture("labelSelectMode").getSize().y / 2 - 150);
    labeles.push_back(new sf::Sprite(resources->getTexture("labelEnterIp")));
    labeles.back()->setPosition(window.getSize().x/2 - resources->getTexture("labelEnterIp").getSize().x / 2,
                                window.getSize().y/2 - resources->getTexture("labelEnterIp").getSize().y / 2 - 150);
    labeles.push_back(new sf::Sprite(resources->getTexture("labelConnecting")));
    labeles.back()->setPosition(window.getSize().x/2 - resources->getTexture("labelConnecting").getSize().x / 2,
                                window.getSize().y/2 - resources->getTexture("labelConnecting").getSize().y / 2 - 100);
    labeles.back()->setTextureRect(sf::IntRect(0, 0, labeles[2]->getTexture()->getSize().x - 60, labeles[2]->getTexture()->getSize().y));
    labeles.push_back(new sf::Sprite(resources->getTexture("labelConnected")));
    labeles.back()->setPosition(window.getSize().x/2 - resources->getTexture("labelConnecting").getSize().x / 2,
                                window.getSize().y/2 - resources->getTexture("labelConnecting").getSize().y / 2 - 100);

    textIp.setCharacterSize(30);
    textIp.setFillColor(sf::Color(180, 120, 255));
    textIp.setFont(resources->getFont("Mylodon-Light"));
    textIp.setString("Your Ip: " + ip.toString());
    auto bounds = textIp.getGlobalBounds();
    textIp.setPosition(window.getSize().x/2 - bounds.width / 2,
                       window.getSize().y/2 - bounds.height / 2 - 150);
}

void MultiplayerMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite, states);
    switch (mpMenuState)
    {
    case MultiplayerMenuStates::MPMS_SELECT_MODE:
        for(auto &i : buttons)
            target.draw(*i, states);
        target.draw(*labeles[0], states);
        break;
    case MultiplayerMenuStates::MPMS_ENTER_IP:
        for(auto &i : enterButtons)
            target.draw(*i, states);
        target.draw(*labeles[1], states);
        target.draw(*textBoxes[0], states);
        break;
    case MultiplayerMenuStates::MPMS_LOBBY:
        for(auto &i : lobbyButtons)
            target.draw(*i, states);
        if(mode == 1)
            target.draw(textIp, states);
        if(connected)
        {
            target.draw(*labeles[3], states);
        }
        else
        {
            target.draw(*labeles[2], states);
        }

        break;
    default:
        break;
    }
}
