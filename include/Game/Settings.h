#ifndef SETTINGS_H
#define SETTINGS_H

struct VideoSettings
{
    unsigned int width;
    unsigned int height;
    unsigned int framerateLimit;
    bool fullscreen;
    bool vsync;
    VideoSettings()
    {
        width = 640;
        height = 480;
        framerateLimit = 200;
        fullscreen = false;
        vsync = false;
    }
};

#endif //SETTINGS_H