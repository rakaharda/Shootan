#include "Game\VideoSettings.h"

VideoSettings::VideoSettings()
{
    width = 640;
    height = 480;
    framerateLimit = 200;
    fullscreen = false;
    vsync = false;
}

bool VideoSettings::loadSettings()
{
    FILE *fp = fopen("settings.conf", "r");
    if (fp == NULL)
    {
        saveSettings();
        return false;
    }
    unsigned int temp;
    fscanf(fp, "Fullscreen=%u\n", &temp);
    fullscreen = (bool)temp;
    fscanf(fp, "Vertical Sync=%u\n", &temp);
    vsync = (bool)temp;
    fscanf(fp, "Width=%u\n", &width);
    fscanf(fp, "Height=%u\n", &height);
    fscanf(fp, "Framerate Limit=%u\n", &framerateLimit);
    fclose(fp);
    if(width < 640)
        width = 640;
    if(height < 480)
        height = 480;
    if(framerateLimit > 200)
        framerateLimit = 200;
    return true;
}

bool VideoSettings::saveSettings()
{
    FILE *fp = fopen("settings.conf", "w");
    if (fp == NULL)
        return false;
    fprintf(fp, "Fullscreen=%u\n", (unsigned)fullscreen);
    fprintf(fp, "Vertical Sync=%u\n", (unsigned)vsync);
    fprintf(fp, "Width=%u\n", width);
    fprintf(fp, "Height=%u\n", height);
    fprintf(fp, "Framerate Limit=%u\n", framerateLimit);
    fclose(fp);
    return true;
}
