#ifndef VIDEOSETTINGS_H
#define VIDEOSETTINGS_H

#include <iostream>

using namespace std;

class VideoSettings
{
    public:
        VideoSettings();
        virtual ~VideoSettings(){};
        unsigned int width;
        unsigned int height;
        unsigned int framerateLimit;
        bool fullscreen;
        bool vsync;
        bool loadSettings();
        bool saveSettings();
};

#endif // VIDEOSETTINGS_H
