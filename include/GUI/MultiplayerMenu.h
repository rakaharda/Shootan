#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include "GUI/Slider.h"
#include "GUI/TextBox.h"
#include "GUI/Menu.h"
#include "GUI/MenuStates.h"
#include "GUI/MultiplayerStates.h"
#include "Utils/ResourceManager.h"
#include "Utils/VideoSettings.h"
#include "Game/GSMPHost.h"
#include "Game/GSMPClient.h"
#include "Components/GameStates.h"

class MultiplayerMenu: public Menu
{
public:
    MultiplayerMenu(GameStates *_gameState, MenuStates *_menuState, VideoSettings *_videoSettings);
    virtual ~MultiplayerMenu();
    void handleEvents(sf::Event event);
    void update();
private:
    void setFunctions();
    void loadResources();
    void setButtons();
    vector<sf::Sprite*> labeles;
    vector<TextBox*> textBoxes;
    vector<Button*> enterButtons;
    vector<Button*> lobbyButtons;
    vector<string> buttonNames;
    vector<sf::Vector2f*> positions;
    MenuStates *menuState;
    GameStates *gameState;
    MultiplayerStates mpMenuState;
    VideoSettings *videoSettings;
    sf::IpAddress ip;
    sf::Text textIp;
    int mode;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern GSMPHost *multiplayerState;

#endif //MULTIPLAYERMENU_H
