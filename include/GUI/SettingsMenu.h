#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "GUI/Menu.h"
#include "GUI/MenuStates.h"
#include "GUI/Slider.h"
#include "Utils/VideoSettings.h"
#include "Utils/AudioSettings.h"
#include "Utils/ResourceManager.h"
#include "GUI/Checkbox.h"

class SettingsMenu: public Menu
{
public:
    SettingsMenu(VideoSettings *_videoSettings, MenuStates *_menuState);
    void handleEvents(sf::Event event);
    void update();
    virtual ~SettingsMenu();
private:
    VideoSettings tempVideoSettings;
    VideoSettings *videoSettings;
    MenuStates *menuState;
    std::function<void(float)> *sliderFunctions;
    vector <Slider*> sliders; 
    void setFunctions();
    void loadResources();
    void refreshVideoMenu();
    void refreshAudioMenu();
    void changeSettings();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;
extern ResourceManager *resources;
extern AudioSettings        *audioSettings;

#endif // SETTINGSMENU_H
