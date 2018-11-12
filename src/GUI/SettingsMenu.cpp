#include "GUI/SettingsMenu.h"
#include <iostream>
SettingsMenu::SettingsMenu(VideoSettings *_videoSettings, bool *_isSettings)
{
    isSettings = _isSettings;
    videoSettings = _videoSettings;
    tempVideoSettings = *videoSettings;
    setFunctions();
    loadResources();
    refreshMenu();
}

SettingsMenu::~SettingsMenu()
{
    //dtor
}

void SettingsMenu::loadResources()
{
    //resources->addTexture("MainSettingsMenuBackground", "./data/GUI/MainSettingsMenu/MainSettingsMenuBackground.png");
    resources->addTexture("buttonMainSettingsLeft",   "./data/GUI/MainSettingsMenu/buttonSettingsLeft.png");
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
    //resources->addTexture("buttonMainSettingsVideoSettngs", "./data/GUI/MainSettingsMenu/");
    //resources->addTexture("MainSettingsMenuBackground", "./data/GUI/MainSettingsMeni/");
    //resources->addTexture("MainSettingsMenuBackground", "./data/GUI/MainSettingsMeni/");
    //resources->addTexture("MainSettingsMenuBackground", "./data/GUI/MainSettingsMeni/");

}

void SettingsMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [10];
    buttonFunctions[0] = [this](){
        if (tempVideoSettings.vsync)
        {
            //buttons[3]->isSelect = false;
            tempVideoSettings.vsync =  false;
            refreshMenu();
        }
        else
        {
            //buttons[3]->isSelect = true;
            tempVideoSettings.vsync = true;
            refreshMenu();
        }
    };

    buttonFunctions[1] = [this](){
        if(tempVideoSettings.selectedResol == 0)
            tempVideoSettings.selectedResol = tempVideoSettings.resolutions.size() - 1;
        else tempVideoSettings.selectedResol--;
        tempVideoSettings.width = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x;
        tempVideoSettings.height = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y;
        refreshMenu();
    };


    buttonFunctions[2] = [this](){
        if(tempVideoSettings.selectedResol == tempVideoSettings.resolutions.size() - 1)
            tempVideoSettings.selectedResol = 0;
        else tempVideoSettings.selectedResol++;
        tempVideoSettings.width = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x;
        tempVideoSettings.height = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y;
        refreshMenu();
    };

    buttonFunctions[3] = [](){};

    buttonFunctions[4] = [this](){
        if(tempVideoSettings.fullscreen)
        {
            tempVideoSettings.fullscreen = false;
            refreshMenu();
        }
        else
        {
            tempVideoSettings.fullscreen = true;
            refreshMenu();
        }
    };

    buttonFunctions[5] = [this](){
        *isSettings = false;
        tempVideoSettings = *videoSettings;
    };

    buttonFunctions[6] = [this](){
        window.close();
        *videoSettings = tempVideoSettings;
        if(videoSettings->fullscreen)
            window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan", sf::Style::Fullscreen);
        else window.create(sf::VideoMode(videoSettings->width, videoSettings->height), "Shootan");
        if (videoSettings->vsync)
                window.setVerticalSyncEnabled(true);
        else window.setVerticalSyncEnabled(false);
        refreshMenu();
    };
}

void SettingsMenu::refreshMenu()
{
    string buttonName[5];
    buttonName[0] = "buttonMainSettingsLeft";
    buttonName[1] = "buttonMainSettingsRight";
    buttonName[2] = "buttonMainSettingsResulution";
    buttonName[2]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x);
    buttonName[2]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y);
    if (tempVideoSettings.fullscreen)
        buttonName[3] = "buttonMainSettingsFullscreen";
    else
        buttonName[3] = "buttonMainSettingsWindowed";
    buttonName[4] = "buttonMainSettingsBack";
    buttonName[5] = "buttonMainSettingsApply";
    buttons.clear();
    buttons.push_back(new CheckBox("Vertical Sync",window.getSize().x / 2,window.getSize().y / 2 - 250,tempVideoSettings.vsync));
    buttons.back()->setFunction(buttonFunctions[0]);
    buttons.push_back(new Button(resources->getTexture(buttonName[0]),window.getSize().x / 2 - 250, window.getSize().y / 2 - 50));
    buttons.back()->setFunction(buttonFunctions[1]);
    buttons.push_back(new Button(resources->getTexture(buttonName[1]),window.getSize().x / 2 + 250, window.getSize().y / 2 - 50));
    buttons.back()->setFunction(buttonFunctions[2]);
    for(int i = 0; i < 2; i++){
        buttons.push_back(new Button(resources->getTexture(buttonName[i+2]),window.getSize().x / 2,window.getSize().y / 2 - 250 + (i + 1)*200));
        buttons.back()->setFunction(buttonFunctions[i+3]);
    }
    buttons.push_back(new Button(resources->getTexture(buttonName[4]),window.getSize().x / 2 - 200, window.getSize().y / 2 + 300));
    buttons.back()->setFunction(buttonFunctions[5]);
    buttons.push_back(new Button(resources->getTexture(buttonName[5]),window.getSize().x / 2 + 200, window.getSize().y / 2 + 300));
    buttons.back()->setFunction(buttonFunctions[6]);
    backGroundSprite.setTexture(resources->getTexture("backgroundMainMenu"));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);
    for(unsigned int i = 0; i < buttons.size(); i++)
        buttonName[i].erase();
}

void SettingsMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
