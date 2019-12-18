#ifndef MULTIPLAYERMENU_H
#define MULTIPLAYERMENU_H

#include "GUI/Menu.h"
#include "GUI/MenuStates.h"
#include "Utils/ResourceManager.h"
#include "Components/GameStates.h"
#include "GUI/Slider.h"
#include "GUI/MultiplayerStates.h"
#include "GUI/TextBox.h"
#include <SFML/Network.hpp>

class MultiplayerMenu: public Menu
{
public:
    MultiplayerMenu(GameStates *_gameState, MenuStates *_menuState, int *_mode);
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
    MultiplayerStates multiplayerState;
    sf::IpAddress ip;
    sf::Text textIp;
    int *mode;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif //MULTIPLAYERMENU_H
