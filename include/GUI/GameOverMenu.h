#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "GUI/Menu.h"
#include "Components/GameStates.h"

class GameOverMenu: public Menu
{
public:
    GameOverMenu();
    virtual ~GameOverMenu();
    void handleEvents(sf::Event event);
    GameStates gameState;
private:
    void loadResources();
    void setFunctions();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // GAMEOVERMENU_H
