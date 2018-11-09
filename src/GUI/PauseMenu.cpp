#include "GUI/PauseMenu.h"

PauseMenu::PauseMenu(VideoSettings *_videoSettings,bool *_menuStatus)
{
    videoSettings = _videoSettings;
    tempVideoSettings = *videoSettings;
    menuStatus = _menuStatus;
    *menuStatus = true;
    isSettings = false;
    setFunctions();
    loadResources();
    string buttonName[3];
    buttonName[0] = "buttonPlay";
    buttonName[1] = "buttonSettings";
    buttonName[2] = "buttonExit";
    for(int i = 0; i < 3; i++){
        buttons.push_back(new Button(resources->getTexture(buttonName[i]),window.getSize().x/2,window.getSize().y/2 - 150 + i*150));
        buttons.back()->setFunction(buttonFunctions[i]);
    }
    for(int i = 0; i < 3; i++)
        buttonName[i].erase();
    backGroundSprite.setTexture(resources->getTexture("backgroundPauseMenu"));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);

}

PauseMenu::~PauseMenu()
{
    //dtor
}

void PauseMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [10];
    buttonFunctions[0] = [this](){
        *menuStatus = false;
    };
    buttonFunctions[1] = [this](){
        string checkBoxText;
        string buttonName[5];
        isSettings = true;
        buttonName[0] = "buttonSettingsLeft";
        buttonName[1] = "buttonSettingsRight";
        buttonName[2] = "buttonSettingsResulution";
        buttonName[2]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x);
        buttonName[2]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y);
        if (tempVideoSettings.fullscreen)
            buttonName[3] = "buttonSettingsFullscreen";
        else
            buttonName[3] = "buttonSettingsWindowed";
        buttonName[4] = "buttonSettingsBack";
        buttonName[5] = "buttonSettingsApply";
        buttons.clear();
        buttons.push_back(new CheckBox("Vertical Sync",window.getSize().x / 2,window.getSize().y / 2 - 300,tempVideoSettings.vsync));
        buttons.back()->setFunction(buttonFunctions[3]);
        buttons.push_back(new Button(resources->getTexture(buttonName[0]),window.getSize().x / 2 - 150, window.getSize().y / 2 - 160));
        buttons.back()->setFunction(buttonFunctions[4]);
        buttons.push_back(new Button(resources->getTexture(buttonName[1]),window.getSize().x / 2 + 150, window.getSize().y / 2 - 160));
        buttons.back()->setFunction(buttonFunctions[5]);

        for(int i = 0; i < 4; i++){
            buttons.push_back(new Button(resources->getTexture(buttonName[i+2]),window.getSize().x / 2,window.getSize().y / 2 - 300 + (i + 1)*140));
            buttons.back()->setFunction(buttonFunctions[i+6]);
        }
        for(unsigned int i = 0; i < 6; i++)
           buttonName[i].erase();
        checkBoxText.erase();
    };
    buttonFunctions[2] = [this](){
        window.close();
    };
    buttonFunctions[3] = [this](){
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

    buttonFunctions[4] = [this](){
        if(tempVideoSettings.selectedResol == 0)
            tempVideoSettings.selectedResol = tempVideoSettings.resolutions.size() - 1;
        else tempVideoSettings.selectedResol--;
        tempVideoSettings.width = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x;
        tempVideoSettings.height = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y;
        refreshMenu();
    };


    buttonFunctions[5] = [this](){
        if(tempVideoSettings.selectedResol == tempVideoSettings.resolutions.size() - 1)
            tempVideoSettings.selectedResol = 0;
        else tempVideoSettings.selectedResol++;
        tempVideoSettings.width = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x;
        tempVideoSettings.height = tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y;
        refreshMenu();
    };

    buttonFunctions[6] = [](){};

    buttonFunctions[7] = [this](){
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

    buttonFunctions[8] = [this](){
        isSettings = false;
        tempVideoSettings = *videoSettings;
        string buttonName[3];
        buttonName[0] = "buttonPlay";
        buttonName[1] = "buttonSettings";
        buttonName[2] = "buttonExit";
        buttons.clear();
        for(int i = 0; i < 3; i++){
            buttons.push_back(new Button(resources->getTexture(buttonName[i]),window.getSize().x/2,window.getSize().y/2 - 150 + i*150));
            buttons.back()->setFunction(buttonFunctions[i]);
        }
        for(int i = 0; i < 3; i++)
            buttonName[i].erase();
    };

    buttonFunctions[9] = [this](){
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


void PauseMenu::refreshMenu()
{
    string buttonName[5];
    isSettings = true;
    buttonName[0] = "buttonSettingsLeft";
    buttonName[1] = "buttonSettingsRight";
    buttonName[2] = "buttonSettingsResulution";
    buttonName[2]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->x);
    buttonName[2]+=to_string(tempVideoSettings.resolutions[tempVideoSettings.selectedResol]->y);
    if (tempVideoSettings.fullscreen)
        buttonName[3] = "buttonSettingsFullscreen";
    else
        buttonName[3] = "buttonSettingsWindowed";
    buttonName[4] = "buttonSettingsBack";
    buttonName[5] = "buttonSettingsApply";
    buttons.clear();
    buttons.push_back(new CheckBox("Vertical Sync",window.getSize().x / 2,window.getSize().y / 2 - 300,tempVideoSettings.vsync));
    buttons.back()->setFunction(buttonFunctions[3]);
    buttons.push_back(new Button(resources->getTexture(buttonName[0]),window.getSize().x / 2 - 150, window.getSize().y / 2 - 160));
    buttons.back()->setFunction(buttonFunctions[4]);
    buttons.push_back(new Button(resources->getTexture(buttonName[1]),window.getSize().x / 2 + 150, window.getSize().y / 2 - 160));
    buttons.back()->setFunction(buttonFunctions[5]);

    for(int i = 0; i < 4; i++){
        buttons.push_back(new Button(resources->getTexture(buttonName[i+2]),window.getSize().x / 2,window.getSize().y / 2 - 300 + (i + 1)*140));
        buttons.back()->setFunction(buttonFunctions[i+6]);
    }

    for(int i = 0; i < 6; i++)
        buttonName[i].erase();
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);
}

void PauseMenu::loadResources()
{
    resources->addTexture("buttonPlay",     "./data/GUI/pauseMenu/buttonPlay.png");
    resources->addTexture("buttonSettings", "./data/GUI/pauseMenu/buttonSettings.png");
    resources->addTexture("buttonExit",     "./data/GUI/pauseMenu/buttonExit.png");
    resources->addTexture("backgroundPauseMenu",      "./data/GUI/pauseMenu/backgroundPauseMenu.png");
    resources->addTexture("buttonSettingsFullscreen", "./data/GUI/settingsMenu/buttonSettingsFullscreen.png");
    resources->addTexture("buttonSettingsWindowed",   "./data/GUI/settingsMenu/buttonSettingsWindowed.png");
    resources->addTexture("buttonSettingsLeft",       "./data/GUI/settingsMenu/buttonSettingsLeft.png");
    resources->addTexture("buttonSettingsRight",      "./data/GUI/settingsMenu/buttonSettingsRight.png");
    resources->addTexture("buttonSettingsBack",       "./data/GUI/settingsMenu/buttonSettingsBack.png");
    resources->addTexture("buttonSettingsApply",      "./data/GUI/settingsMenu/buttonSettingsApply.png");
    resources->addTexture("buttonSettingsMark",       "./data/GUI/settingsMenu/buttonSettingsMark.png");
    resources->addTexture("buttonSettingsMarkBorder", "./data/GUI/settingsMenu/buttonSettingsMarkBorder.png");
    resources->addTexture("buttonSettingsResulution38402160",      "./data/GUI/settingsMenu/resolutions/buttonSettingsResulution38402160.png");
    resources->addTexture("buttonSettingsResulution19201080",      "./data/GUI/settingsMenu/resolutions/buttonSettingsResulution19201080.png");
    resources->addTexture("buttonSettingsResulution1600900",       "./data/GUI/settingsMenu/resolutions/buttonSettingsResulution1600900.png");
    resources->addTexture("buttonSettingsResulution1366768",       "./data/GUI/settingsMenu/resolutions/buttonSettingsResulution1366768.png");
    resources->addTexture("buttonSettingsResulution1280720",       "./data/GUI/settingsMenu/resolutions/buttonSettingsResulution1280720.png");
    resources->addTexture("buttonSettingsResulution1024768",       "./data/GUI/settingsMenu/resolutions/buttonSettingsResulution1024768.png");
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
