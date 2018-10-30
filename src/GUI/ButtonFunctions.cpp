#include "GUI/ButtonFunctions.h"

void switchWindowMode(VideoSettings* videoSettings)
{
    if(videoSettings->fullscreen)
    {
        window.close();
        window.create(sf::VideoMode(1280, 720), "Shootan");
        if (*verticalSync)
            window.setVerticalSyncEnabled(true);
        changeButtonName("Windowed");
        videoSettings->fullscreen = false;
    }
    else
    {
        window.close();
        window.create(sf::VideoMode(1280, 720), "Shootan", sf::Style::Fullscreen);
        if (*verticalSync)
            window.setVerticalSyncEnabled(true);
        changeButtonName("Fullscreen");
        videoSettings->fullscreen = true;
    }
    break;
}

void switchResolution(VideoSettings* videoSettings)
{
    int a = 0;
    a++;
}

void playGame(bool *menuStatus)
{
    menuStatus = false;
}

void exitGame(bool *isPlaying)
{
    window.close();
    isPlaying = 0;
}

void createSettingsMenu()
{


}

void switchVSync(VideoSettings* videoSettings)
{
    if (videoSettings->verticalSync)
    {
        isSelect = false;
        videoSettings->verticalSync =  false;
        window.setVerticalSyncEnabled(false);
    }
    else
    {
        isSelect = true;
        videoSettings->verticalSync = true;
        window.setVerticalSyncEnabled(true);
    }
}

extern sf::RenderWindow window;