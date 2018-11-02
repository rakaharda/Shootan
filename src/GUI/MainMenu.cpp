#include "GUI/MainMenu.h"

MainMenu::MainMenu(VideoSettings *_videoSettings,bool *_menuStatus, bool *_isPlaing)
{
    videoSettings = _videoSettings;
    isPlaying = _isPlaing;
    menuStatus = _menuStatus;
    *menuStatus = true;
    isSettings = false;
    setFunctions();
    string str[4];
    str[0] = "Play";
    str[1] = "Settings";
    str[2] = "Exit";
    str[3] = "./data/interface/button.png";
    for(int i = 0; i < 3; i++)
        buttons.push_back(new Button(str[i],str[3],30.f,window.getSize().x/2,window.getSize().y/2 - 150 + i*150, buttonFunctions[i]));
    for(int i = 0; i < 4; i++)
        str[i].erase();
    backGroundTexture.loadFromFile("./data/interface/background.png");
    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);

}

MainMenu::~MainMenu()
{
    //dtor
}

void MainMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [7];
    buttonFunctions[0] = [this](){
        *menuStatus = false;
    };
    buttonFunctions[1] = [this](){
        string str[5];
        isSettings = true;
        str[0] = "Vertical Sync";
        if (videoSettings->fullscreen)
            str[1] = "Fullscreen";
        else
            str[1] = "Windowed";
        if (window.getSize().x == 1280)
            str[2] = "720";
        if (window.getSize().x == 1920)
            str[2] = "1080";
        str[3] = "Back";
        str[4] = "./data/interface/button4.png";
        buttons.clear();
        buttons.push_back(new CheckBox(str[0],28.f,window.getSize().x / 2,window.getSize().y / 2 - 176,videoSettings->vsync,buttonFunctions[3]));
        for(int i = 1; i < 4; i++)
            buttons.push_back(new Button(str[i],str[4],30.f,window.getSize().x / 2,window.getSize().y / 2 - 176 + i*116, buttonFunctions[i+3]));
        for(int i = 0; i < 5; i++)
            str[i].erase();
    };
    buttonFunctions[2] = [this](){
        window.close();
        *isPlaying = true;
    };
    buttonFunctions[3] = [this](){
        if (videoSettings->vsync)
        {
            buttons[3]->isSelect = false;
            videoSettings->vsync =  false;
            window.setVerticalSyncEnabled(false);
            refreshMenu();
        }
        else
        {
            buttons[3]->isSelect = true;
            videoSettings->vsync = true;
            window.setVerticalSyncEnabled(true);
            refreshMenu();
        }
    };
    buttonFunctions[4] = [this](){
        if(videoSettings->fullscreen)
        {
            window.close();
            window.create(sf::VideoMode(1280, 720), "Shootan");
            if (videoSettings->vsync)
                window.setVerticalSyncEnabled(true);
            videoSettings->fullscreen = false;
            refreshMenu();
        }
        else
        {
            window.close();
            window.create(sf::VideoMode(1280, 720), "Shootan", sf::Style::Fullscreen);
            if (videoSettings->vsync)
                window.setVerticalSyncEnabled(true);
            videoSettings->fullscreen = true;
            refreshMenu();
        }
    };
    buttonFunctions[5] = [this](){
        if(videoSettings->height == 1280)
        {
            window.close();
            if(videoSettings->fullscreen)
                window.create(sf::VideoMode(1920, 1080), "Shootan", sf::Style::Fullscreen);
            else
                window.create(sf::VideoMode(1920, 1080), "Shootan");
            if (videoSettings->vsync)
                window.setVerticalSyncEnabled(true);
            videoSettings->width = 1080;
            videoSettings->height = 1920;
            refreshMenu();
        }
        else
        {
            window.close();
            if(videoSettings->fullscreen)
                window.create(sf::VideoMode(1280, 720), "Shootan", sf::Style::Fullscreen);
            else
                window.create(sf::VideoMode(1280, 720), "Shootan");
            if (videoSettings->vsync)
                window.setVerticalSyncEnabled(true);
            videoSettings->width = 720;
            videoSettings->height = 1280;
            refreshMenu();
        }
    };
    buttonFunctions[6] = [this](){
        isSettings = false;
        string str[4];
        str[0] = "Play";
        str[1] = "Settings";
        str[2] = "Exit";
        str[3] = "./data/interface/button.png";
        buttons.clear();
        for(int i = 0; i < 3; i++)
            buttons.push_back(new Button(str[i],str[3],30.f,window.getSize().x / 2,window.getSize().y / 2 - 150 + i*150,buttonFunctions[i]));
        for(int i = 0; i < 4; i++)
            str[i].erase();
    };
}

void MainMenu::refreshMenu()
{
    string str[5];
    isSettings = true;
    str[0] = "Vertical Sync";
    if (videoSettings->fullscreen)
        str[1] = "Fullscreen";
    else
        str[1] = "Windowed";
    if (window.getSize().x == 1280)
        str[2] = "720";
    if (window.getSize().x == 1920)
        str[2] = "1080";
    str[3] = "Back";
    str[4] = "./data/interface/button4.png";
    buttons.clear();
    buttons.push_back(new CheckBox(str[0],28.f,window.getSize().x / 2,window.getSize().y / 2 - 176,videoSettings->vsync, buttonFunctions[3]));
    for(int i = 1; i < 4; i++)
        buttons.push_back(new Button(str[i],str[4],30.f,window.getSize().x / 2,window.getSize().y / 2 - 176 + i*116, buttonFunctions[i+3]));
    for(int i = 0; i < 5; i++)
        str[i].erase();
    backGroundSprite.setPosition(window.getSize().x / 2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y / 2 - backGroundSprite.getTexture()->getSize().y / 2);

}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite,states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i],states);
}
