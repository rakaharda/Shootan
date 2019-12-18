#ifndef MAINMENU_H
#define MAINMENU_H

#include "GUI/Menu.h"
#include "GUI/MenuStates.h"
#include "Utils/ResourceManager.h"
#include "Utils/AudioSettings.h"
#include "Utils/VideoSettings.h"
#include "Components/GameStates.h"
#include "GUI/Slider.h"

class MainMenu: public Menu
{
public:
    MainMenu(GameStates *_gameState, MenuStates *_menuState);
    void handleEvents(sf::Event event);
    virtual ~MainMenu();
    void playCaption();
    void stopCaption();
    bool isCaption();
    void caption();
    void uncaption();
    void update();
private:
    void setFunctions();
    void loadResources();
    bool m_isCaption;
    sf::Sprite captionSprite;
    sf::Sprite backgroundCaption;
    MenuStates *menuState;
    GameStates *gameState;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern AudioSettings *audioSettings;
extern sf::RenderWindow window;
extern ResourceManager *resources;

#endif // MAINMENU_H
