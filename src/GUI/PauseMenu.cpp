#include "GUI/PauseMenu.h"

PauseMenu::PauseMenu(VideoSettings *_videoSettings,bool *_menuStatus)
{
    gameState = GameStates::GS_GAMEMODE_SURVIVAL;
    videoSettings = _videoSettings;
    tempVideoSettings = *videoSettings;
    menuStatus = _menuStatus;
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
        buttons.back()->setLightButton(buttonName[i]+"Light");
    }
    backGroundSprite.setTexture(resources->getTexture("backgroundPauseMenu"));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);

}

PauseMenu::~PauseMenu()
{
    resources->deleteTexture("buttonPlay");
    resources->deleteTexture("buttonSettings");
    resources->deleteTexture("buttonExit");
    resources->deleteTexture("buttonPlayLight");
    resources->deleteTexture("buttonSettingsLight");
    resources->deleteTexture("buttonExitLight");
    resources->deleteTexture("buttonSettingsFullscreen");
    resources->deleteTexture("buttonSettingsWindowed");
    resources->deleteTexture("buttonSettingsBack");
    resources->deleteTexture("buttonSettingsFullscreenLight");
    resources->deleteTexture("buttonSettingsWindowedLight");
    resources->deleteTexture("buttonSettingsBackLight");
    resources->deleteTexture("Music_Volume");
    resources->deleteTexture("Effects_Volume");
    resources->deleteTexture("sliderLine");
    resources->deleteTexture("sliderButton");
    resources->deleteTexture("backgroundPauseMenu");
}

void PauseMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [5];
    sliderFunctions = new std::function<void(float)> [2];
    buttonFunctions[0] = [this](){
        *menuStatus = false;
    };
    buttonFunctions[1] = [this](){
       refreshMenu();
    };
    buttonFunctions[2] = [this](){
        gameState = GameStates::GS_MAINMENU;
    };

    buttonFunctions[3] = [this](){
        if(tempVideoSettings.fullscreen)
            tempVideoSettings.fullscreen = false;
        else
            tempVideoSettings.fullscreen = true;
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

    buttonFunctions[4] = [this](){
        isSettings = false;
        tempVideoSettings = *videoSettings;
        string buttonName[3];
        buttonName[0] = "buttonPlay";
        buttonName[1] = "buttonSettings";
        buttonName[2] = "buttonExit";
        buttons.clear();
        sliders.clear();
        for(int i = 0; i < 3; i++){
            buttons.push_back(new Button(resources->getTexture(buttonName[i]),window.getSize().x/2,window.getSize().y/2 - 150 + i*150));
            buttons.back()->setFunction(buttonFunctions[i]);
            buttons.back()->setLightButton(buttonName[i]+"Light");
        }
    };

    sliderFunctions[0] = [](float status){
        resources->getMusic("GXRCH - HARD")->setVolume(status);
    };
    sliderFunctions[1] = [](float status) {
        float musicVolume = resources->getMusic("GXRCH - HARD")->getVolume();
        sf::Listener::setGlobalVolume(status);
        resources->getMusic("GXRCH - HARD")->setVolume(musicVolume);
    };
}


void PauseMenu::refreshMenu()
{
    string buttonName[2];
    isSettings = true;
    if (tempVideoSettings.fullscreen)
        buttonName[0] = "buttonSettingsFullscreen";
    else
        buttonName[0] = "buttonSettingsWindowed";
    buttonName[1] = "buttonSettingsBack";
    buttons.clear();
    sliders.clear();
    sliders.push_back(new Slider("Music_Volume",window.getSize().x / 2,window.getSize().y / 2 - 150,resources->getMusic("GXRCH - HARD")->getVolume()));
    sliders.back()->setFunction(sliderFunctions[0]);
    sliders.push_back(new Slider("Effects_Volume",window.getSize().x / 2,window.getSize().y / 2 - 40, resources->getMusic("assaultrifle_shot")->getVolume()));
    sliders.back()->setFunction(sliderFunctions[1]);
    buttons.push_back(new Button(resources->getTexture(buttonName[0]),window.getSize().x / 2,window.getSize().y / 2 + 80));
    buttons.back()->setFunction(buttonFunctions[3]);
    buttons.back()->setLightButton(buttonName[0]+"Light");
    buttons.push_back(new Button(resources->getTexture(buttonName[1]),window.getSize().x / 2,window.getSize().y / 2 + 200));
    buttons.back()->setFunction(buttonFunctions[4]);
    buttons.back()->setLightButton(buttonName[1]+"Light");
}

void PauseMenu::loadResources()
{
    resources->addTexture("buttonPlay",     "./data/GUI/pauseMenu/buttonPlay.png");
    resources->addTexture("buttonSettings", "./data/GUI/pauseMenu/buttonSettings.png");
    resources->addTexture("buttonExit",     "./data/GUI/pauseMenu/buttonExit.png");
    resources->addTexture("buttonPlayLight",     "./data/GUI/pauseMenu/buttonPlayLight.png");
    resources->addTexture("buttonSettingsLight", "./data/GUI/pauseMenu/buttonSettingsLight.png");
    resources->addTexture("buttonExitLight",     "./data/GUI/pauseMenu/buttonExitLight.png");
    resources->addTexture("buttonSettingsFullscreen",     "./data/GUI/settingsMenu/buttonSettingsFullscreen.png");
    resources->addTexture("buttonSettingsWindowed",       "./data/GUI/settingsMenu/buttonSettingsWindowed.png");
    resources->addTexture("buttonSettingsBack",           "./data/GUI/settingsMenu/buttonSettingsBack.png");
    resources->addTexture("buttonSettingsFullscreenLight",     "./data/GUI/settingsMenu/buttonSettingsFullscreenLight.png");
    resources->addTexture("buttonSettingsWindowedLight",       "./data/GUI/settingsMenu/buttonSettingsWindowedLight.png");
    resources->addTexture("buttonSettingsBackLight",           "./data/GUI/settingsMenu/buttonSettingsBackLight.png");
    resources->addTexture("Music_Volume",         "./data/GUI/settingsMenu/sliderTextMusicVolume.png");
    resources->addTexture("Effects_Volume",       "./data/GUI/settingsMenu/sliderTextEffectsVolume.png");
    resources->addTexture("sliderLine",   "./data/GUI/settingsMenu/sliderLineSettingsMenu.png");
    resources->addTexture("sliderButton", "./data/GUI/settingsMenu/sliderSettingsMenu.png");
    resources->addTexture("backgroundPauseMenu",      "./data/GUI/pauseMenu/backgroundPauseMenu.png");
}

void PauseMenu::handleEvents(sf::Event event)
{
    for(unsigned int i = 0; i < buttons.size(); i++)
        buttons[i]->update();
    for(unsigned int i = 0; i < sliders.size(); i++)
        if(sliders[i]->isPressed())
            return;
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
        break;
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
        {      
            buttonFunctions[4]();    
        }
        break;
    default:
        break;
    }
}

void PauseMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
    for(unsigned int i = 0; i < sliders.size(); i++)
        target.draw(*sliders[i],states);
}
