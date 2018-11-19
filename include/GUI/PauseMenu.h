#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"
#include "GUI/Button.h"
#include "GUI/CheckBox.h"
#include "GUI/Slider.h"
#include "Utils/VideoSettings.h"
#include "Components/GameStates.h"
#include "Utils/ResourceManager.h"

class PauseMenu: public Menu
{
public:
    PauseMenu(VideoSettings *_videoSettings, bool *_menuStatus);
    virtual ~PauseMenu();
    void handleEvents(sf::Event event);
    GameStates gameState;
private:
    void refreshMenu();
    void setFunctions();
    void loadResources();
    bool isSettings;
    bool *isPlaying;
    vector <Slider*> sliders;
    std::function<void(float)> *sliderFunctions;
    VideoSettings tempVideoSettings;
    VideoSettings *videoSettings;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
friend Button;
//    buttonFunctions;
};

extern sf::RenderWindow window;
extern ResourceManager      *resources;

#endif // PAUSEMENU_H
