#ifndef MAINMENU_H
#define MAINMENU_H

#include "GUI/Menu.h"
#include "Utils/ResourceManager.h"
#include "Components/GameStates.h"
#include "GUI/Slider.h"

class MainMenu: public Menu
{
public:
    MainMenu(GameStates *_gameState, bool *_isSettings);
    void handleEvents(sf::Event event);
    virtual ~MainMenu();
private:
    void setFunctions();
    void loadResources();
    bool *isSettings;
    GameStates *gameState;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern ResourceManager *resources;

#endif // MAINMENU_H
