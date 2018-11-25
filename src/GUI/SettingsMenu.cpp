#include "GUI/SettingsMenu.h"
#include <iostream>
SettingsMenu::SettingsMenu(VideoSettings *_videoSettings, MenuStates *_menuState)
{
    menuState = _menuState;
    videoSettings = _videoSettings;
    tempVideoSettings = *videoSettings;
    *menuState = MenuStates::MS_SETTINGS_MENU;
    setFunctions();
    loadResources();
    refreshVideoMenu();
}

SettingsMenu::~SettingsMenu()
{
    resources->deleteTexture("buttonMainPlayLight");
    resources->deleteTexture("buttonMainSettingsLight");
    resources->deleteTexture("buttonMainCreditsLight");
    resources->deleteTexture("buttonMainExitLight");
    resources->deleteTexture("backgroundMainMenu");
    resources->deleteTexture("mainSettingsMenuBackground");
    resources->deleteTexture("buttonMainSettingsVideo");
    resources->deleteTexture("buttonMainSettingsAudio");
    resources->deleteTexture("buttonMainSettingsLeft");
    resources->deleteTexture("buttonMainSettingsRight");
    resources->deleteTexture("buttonMainSettingsBack");
    resources->deleteTexture("buttonMainSettingsApply");
    resources->deleteTexture("buttonMainSettingsFullscreen");
    resources->deleteTexture("buttonMainSettingsWindowed");
    resources->deleteTexture("buttonMainSettingsResulution38402160");
    resources->deleteTexture("buttonMainSettingsResulution19201080");
    resources->deleteTexture("buttonMainSettingsResulution1600900");
    resources->deleteTexture("buttonMainSettingsResulution1366768");
    resources->deleteTexture("buttonMainSettingsResulution1280720");
    resources->deleteTexture("buttonMainSettingsResulution1024768");
    resources->deleteTexture("buttonSettingsMark");
    resources->deleteTexture("buttonSettingsMarkBorder");
    resources->deleteTexture("sliderLine");
    resources->deleteTexture("sliderButton");
}

void SettingsMenu::loadResources()
{
    resources->addTexture("mainSettingsMenuBackground", "./data/GUI/MainSettingsMenu/mainSettingsMenuBackground.png");
    resources->addTexture("buttonMainSettingsVideo",   "./data/GUI/MainSettingsMenu/buttonSettingsVideo.png");
    resources->addTexture("buttonMainSettingsAudio",   "./data/GUI/MainSettingsMenu/buttonSettingsAudio.png");
    resources->addTexture("buttonMainSettingsLeft",  "./data/GUI/MainSettingsMenu/buttonSettingsleft.png");
    resources->addTexture("buttonMainSettingsRight",  "./data/GUI/MainSettingsMenu/buttonSettingsRight.png");
    resources->addTexture("buttonMainSettingsBack",   "./data/GUI/MainSettingsMenu/buttonSettingsBack.png");
    resources->addTexture("buttonMainSettingsApply",  "./data/GUI/MainSettingsMenu/buttonSettingsApply.png");
    resources->addTexture("buttonMainSettingsFullscreen", "./data/GUI/mainSettingsMenu/buttonSettingsFullscreen.png");
    resources->addTexture("buttonMainSettingsWindowed",   "./data/GUI/mainSettingsMenu/buttonSettingsWindowed.png");
    resources->addTexture("buttonMainSettingsResulution38402160",      "./data/GUI/mainSettingsMenu/resolutions/buttonSettingsResulution38402160.png");
    resources->addTexture("buttonMainSettingsResulution19201080",      "./data/GUI/mainSettingsMenu/resolutions/buttonSettingsResulution19201080.png");
    resources->addTexture("buttonMainSettingsResulution1600900",       "./data/GUI/mainSettingsMenu/resolutions/buttonSettingsResulution1600900.png");
    resources->addTexture("buttonMainSettingsResulution1366768",       "./data/GUI/mainSettingsMenu/resolutions/buttonSettingsResulution1366768.png");
    resources->addTexture("buttonMainSettingsResulution1280720",       "./data/GUI/mainSettingsMenu/resolutions/buttonSettingsResulution1280720.png");
    resources->addTexture("buttonMainSettingsResulution1024768",       "./data/GUI/mainSettingsMenu/resolutions/buttonSettingsResulution1024768.png");
    resources->addTexture("buttonSettingsMark",       "./data/GUI/mainSettingsMenu/buttonSettingsMark.png");
    resources->addTexture("buttonSettingsMarkBorder", "./data/GUI/mainSettingsMenu/buttonSettingsMarkBorder.png");
    resources->addTexture("Vertical_Sync", "./data/GUI/mainSettingsMenu/checkMarkTextVSync.png");
    resources->addTexture("sliderLine", "./data/GUI/mainSettingsMenu/sliderLineMainSettingsMenu.png");
    resources->addTexture("sliderButton", "./data/GUI/mainSettingsMenu/sliderMainSettingsMenu.png");
    resources->addTexture("Music_Volume",         "./data/GUI/mainSettingsMenu/sliderTextMusicVolume.png");
    resources->addTexture("Effects_Volume",       "./data/GUI/mainSettingsMenu/sliderTextEffectsVolume.png");
    resources->addTexture("General_Volume",         "./data/GUI/mainSettingsMenu/sliderTextGeneralVolume.png");

    resources->addTexture("buttonMainSettingsVideoLight",   "./data/GUI/MainSettingsMenu/buttonSettingsVideoLight.png");
    resources->addTexture("buttonMainSettingsAudioLight",   "./data/GUI/MainSettingsMenu/buttonSettingsAudioLight.png");
    resources->addTexture("buttonMainSettingsBackLight",   "./data/GUI/MainSettingsMenu/buttonSettingsBackLight.png");
    resources->addTexture("buttonMainSettingsApplyLight",  "./data/GUI/MainSettingsMenu/buttonSettingsApplyLight.png");
    resources->addTexture("buttonMainSettingsFullscreenLight", "./data/GUI/mainSettingsMenu/buttonSettingsFullscreenLight.png");
    resources->addTexture("buttonMainSettingsWindowedLight",   "./data/GUI/mainSettingsMenu/buttonSettingsWindowedLight.png");
    resources->addTexture("buttonMainSettingsLeftLight",  "./data/GUI/MainSettingsMenu/buttonSettingsleftLight.png");
    resources->addTexture("buttonMainSettingsRightLight",  "./data/GUI/MainSettingsMenu/buttonSettingsRightLight.png");

}

void SettingsMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [9];
    sliderFunctions = new std::function<void(float)> [3];

    buttonFunctions[0] = [this](){
        refreshVideoMenu();
    };

    buttonFunctions[1] = [this](){
        refreshAudioMenu();
    };

    buttonFunctions[2] = [this](){
        if (tempVideoSettings.vsync)
        {
            tempVideoSettings.vsync =  false;
            refreshVideoMenu();
        }
        else
        {
            tempVideoSettings.vsync = true;
            refreshVideoMenu();
        }
    };

    buttonFunctions[3] = [this](){
        if(tempVideoSettings.selectedResol == 0)
            tempVideoSettings.selectedResol = tempVideoSettings.resolutions.size() - 1;
        else tempVideoSettings.selectedResol--;
        tempVideoSettings.width = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x;
        tempVideoSettings.height = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y;
        refreshVideoMenu();
    };

    buttonFunctions[4] = [this](){
        if(tempVideoSettings.selectedResol == tempVideoSettings.resolutions.size() - 1)
            tempVideoSettings.selectedResol = 0;
        else tempVideoSettings.selectedResol++;
        tempVideoSettings.width = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x;
        tempVideoSettings.height = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y;
        refreshVideoMenu();
    };

    buttonFunctions[5] = [](){};

    buttonFunctions[6] = [this](){
        if(tempVideoSettings.fullscreen)
        {
            tempVideoSettings.fullscreen = false;
            refreshVideoMenu();
        }
        else
        {
            tempVideoSettings.fullscreen = true;
            refreshVideoMenu();
        }
    };

    buttonFunctions[7] = [this](){
        *menuState = MenuStates::MS_CREATE_MAIN_MENU;
        //tempVideoSettings = *videoSettings;
    };

    buttonFunctions[8] = [this](){
        window.close();
        *videoSettings = tempVideoSettings;
        videoSettings->saveSettings();
        if(videoSettings->fullscreen)
            window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan", sf::Style::Fullscreen);
        else window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan");
        if (videoSettings->vsync)
                window.setVerticalSyncEnabled(true);
        else window.setVerticalSyncEnabled(false);
        refreshVideoMenu();
    };

    sliderFunctions[0] = [](float status){
        audioSettings->general = status;
    };

    sliderFunctions[1] = [](float status){
        audioSettings->music = status;
    };

    sliderFunctions[2] = [](float status){
        audioSettings->sounds = status;
    };
}

void SettingsMenu::refreshVideoMenu()
{
    string buttonName[7];
    buttonName[0] = "buttonMainSettingsVideo";
    buttonName[1] = "buttonMainSettingsAudio";
    buttonName[2] = "buttonMainSettingsLeft";
    buttonName[3] = "buttonMainSettingsRight";
    buttonName[4] = "buttonMainSettingsResulution";
    buttonName[4]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x);
    buttonName[4]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y);
    if (tempVideoSettings.fullscreen)
        buttonName[5] = "buttonMainSettingsFullscreen";
    else
        buttonName[5] = "buttonMainSettingsWindowed";
    buttonName[6] = "buttonMainSettingsBack";
    buttonName[7] = "buttonMainSettingsApply";
    backGroundSprite.setTexture(resources->getTexture("mainSettingsMenuBackground"));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);
    sliders.clear();
    buttons.clear();
    buttons.push_back(new Button(resources->getTexture(buttonName[0]),window.getSize().x / 2 - 150, window.getSize().y / 2 - 200));
    buttons.push_back(new Button(resources->getTexture(buttonName[1]),window.getSize().x / 2, window.getSize().y / 2 - 200));
    buttons.back()->setFunction(buttonFunctions[1]);
    buttons.back()->setLightButton(buttonName[1]+"Light");
    buttons.push_back(new CheckBox("Vertical_Sync",window.getSize().x / 2 - 130, window.getSize().y / 2 - 100,tempVideoSettings.vsync));
    buttons.back()->setFunction(buttonFunctions[2]);
    buttons.push_back(new Button(resources->getTexture(buttonName[2]), window.getSize().x / 2 - 190, window.getSize().y / 2));
    buttons.back()->setFunction(buttonFunctions[3]);
    buttons.back()->setLightButton(buttonName[2]+"Light");
    buttons.push_back(new Button(resources->getTexture(buttonName[3]), window.getSize().x / 2 + 190, window.getSize().y / 2));
    buttons.back()->setFunction(buttonFunctions[4]);
    buttons.back()->setLightButton(buttonName[3]+"Light");
    buttons.push_back(new Button(resources->getTexture(buttonName[4]), window.getSize().x / 2,window.getSize().y / 2));
    buttons.back()->setFunction(buttonFunctions[5]);
    buttons.push_back(new Button(resources->getTexture(buttonName[5]), window.getSize().x / 2,window.getSize().y / 2 + 100));
    buttons.back()->setFunction(buttonFunctions[6]);
    buttons.back()->setLightButton(buttonName[5]+"Light");
    buttons.push_back(new Button(resources->getTexture(buttonName[6]), window.getSize().x / 2 - 130, window.getSize().y / 2 + 200));
    buttons.back()->setFunction(buttonFunctions[7]);
    buttons.back()->setLightButton(buttonName[6]+"Light");
    changeSettings();
    for(unsigned int i = 0; i < buttons.size(); i++)
        buttonName[i].erase();
}

void SettingsMenu::refreshAudioMenu()
{
    string buttonName[3];
    buttonName[0] = "buttonMainSettingsVideo";
    buttonName[1] = "buttonMainSettingsAudio";
    buttonName[2] = "buttonMainSettingsBack";
    sliders.clear();
    buttons.clear();
    buttons.push_back(new Button(resources->getTexture(buttonName[0]),window.getSize().x / 2 - 150, window.getSize().y / 2 - 200));
    buttons.back()->setFunction(buttonFunctions[0]);
    buttons.back()->setLightButton(buttonName[0]+"Light");
    buttons.push_back(new Button(resources->getTexture(buttonName[1]),window.getSize().x / 2, window.getSize().y / 2 - 200));
    buttons.push_back(new Button(resources->getTexture(buttonName[2]), window.getSize().x / 2 - 130, window.getSize().y / 2 + 200));
    buttons.back()->setLightButton(buttonName[2]+"Light");
    buttons.back()->setFunction(buttonFunctions[7]);
    sliders.push_back(new Slider("General_Volume",window.getSize().x/2,window.getSize().y/2 - 120,audioSettings->general));
    sliders.back()->setFunction(sliderFunctions[0]);
    sliders.push_back(new Slider("Music_Volume",window.getSize().x/2,window.getSize().y/2,audioSettings->music));
    sliders.back()->setFunction(sliderFunctions[1]);
    sliders.push_back(new Slider("Effects_Volume",window.getSize().x/2,window.getSize().y/2 + 120,audioSettings->sounds));
    sliders.back()->setFunction(sliderFunctions[2]);
}

bool SettingsMenu::changeSettings()
{   string buttonName = "buttonMainSettingsApply";
    if((tempVideoSettings.fullscreen != videoSettings->fullscreen || tempVideoSettings.vsync != videoSettings->vsync ||
        tempVideoSettings.selectedResol != videoSettings->selectedResol) && buttons.size() < 9)
    {
        buttons.push_back(new Button(resources->getTexture(buttonName),window.getSize().x / 2 + 130, window.getSize().y / 2 + 200));
        buttons.back()->setFunction(buttonFunctions[8]);
        buttons.back()->setLightButton(buttonName + "Light");
        return true;
    }
    if (buttons.size() == 9)
        buttons.pop_back();
    return false;
}

void SettingsMenu::handleEvents(sf::Event event)
{
    for(unsigned int i = 0; i < sliders.size(); i++)
    {
        if(sliders[i]->isPressed())
        {
            return;
        }
    }
    for(unsigned int i = 0; i < buttons.size(); i++)
        buttons[i]->update();
    switch(event.type)
    {
    case sf::Event::MouseButtonPressed:
        switch(event.mouseButton.button)
        {
        case sf::Mouse::Left:
            searchButton();
            break;
        default:
            break;
        }
    default:
        break;
    }
}

void SettingsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
    for(unsigned int i = 0; i < sliders.size(); i++)
        target.draw(*sliders[i],states);
}
