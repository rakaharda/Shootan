#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "Menu.h"
#include "Game/SurvivalStates.h"
#include "GUI/Button.h"
#include "GUI/CheckBox.h"
#include "GUI/Slider.h"
#include "Utils/VideoSettings.h"
#include "Components/GameStates.h"
#include "Utils/ResourceManager.h"
#include "Utils/AudioSettings.h"

class PauseMenu: public Menu
{
public:
    PauseMenu(VideoSettings *_videoSettings, SurvivalStates *_survivalState);
    virtual ~PauseMenu();
    void handleEvents(sf::Event event);
    GameStates getGameState();
    void setGameState(GameStates _gameState);
private:
    void refreshMenu();
    void setFunctions();
    void loadResources();
    bool isSettings;
    bool *isPlaying;
    SurvivalStates *survivalState;
    vector <Slider*> sliders;
    std::function<void(float)> *sliderFunctions;
    VideoSettings tempVideoSettings;
    VideoSettings *videoSettings;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    GameStates gameState;
friend Button;
//    buttonFunctions;
};

extern sf::RenderWindow window;
extern ResourceManager      *resources;
extern AudioSettings        *audioSettings;

#endif // PAUSEMENU_H
