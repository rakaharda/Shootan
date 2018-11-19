#ifndef VIDEOSETTINGS_H
#define VIDEOSETTINGS_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class VideoSettings
{
public:
    VideoSettings();
    virtual ~VideoSettings() {};
    unsigned int width;
    unsigned int height;
    unsigned int framerateLimit;
    unsigned int selectedResol;
    vector <sf::Vector2u*> resolutions;
    void fillResolutions();
    bool fullscreen;
    bool vsync;
    bool loadSettings();
    bool saveSettings();
};

#endif // VIDEOSETTINGS_H
