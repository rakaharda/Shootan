#ifndef AUDIOSETTINGS_H
#define AUDIOSETTINGS_H

#include <iostream>

using namespace std;

class AudioSettings
{
public:
    AudioSettings();
    virtual ~AudioSettings();
    float general;
    float music;
    float sounds;
    bool loadSettings();
    bool saveSettings();
};

#endif // AUDIOSETTINGS_H
