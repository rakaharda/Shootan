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
    void update();
    GameStates getGameState();
    void setGameState(GameStates _gameState);
private:
    void loadResources();
    void setFunctions();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    GameStates gameState;
};

#endif // GAMEOVERMENU_H
