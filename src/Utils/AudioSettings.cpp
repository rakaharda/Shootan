#include "Utils\AudioSettings.h"

AudioSettings::AudioSettings() :
    general(100.f),
    music(100.f),
    sounds(100.f)
{

}

AudioSettings::~AudioSettings()
{
    //dtor
}

bool AudioSettings::loadSettings()
{
    FILE *fp = fopen("audio.conf", "r");
    if (fp == NULL)
    {
        saveSettings();
        return false;
    }
    fscanf(fp, "General=%f\n", &general);
    fscanf(fp, "Music=%f\n", &music);
    fscanf(fp, "Sounds=%f\n", &sounds);
    fclose(fp);
    if(general < 0.f)
        general = 0.f;
    if(general > 100.f)
        general = 100.f;
    if(music < 0.f)
        music = 0.f;
    if(music > 100.f)
        music = 100.f;
    if(sounds < 0.f)
        sounds = 0.f;
    if(sounds > 100.f)
        sounds = 100.f;
    return true;
}

bool AudioSettings::saveSettings()
{
    FILE *fp = fopen("audio.conf", "w");
    if (fp == NULL)
        return false;
    fprintf(fp, "General=%f\n", general);
    fprintf(fp, "Music=%f\n", music);
    fprintf(fp, "Sounds=%f\n", sounds);
    fclose(fp);
    return true;
}
