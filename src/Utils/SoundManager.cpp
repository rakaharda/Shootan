#include "Utils\SoundManager.h"

SoundManager::SoundManager()
{
    //ctor
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::addSound(sf::SoundBuffer soundBuffer, float volume, float posX, float posY, float minDistance)
{
    soundsDeq.push_back(sf::Sound());
    soundsDeq.back().setBuffer(soundBuffer);
    soundsDeq.back().setVolume(volume);
    soundsDeq.back().setPosition(posX, posY, 0.f);
    soundsDeq.back().setMinDistance(minDistance);
    soundsDeq.back().play();
}

void SoundManager::clearDeq()
{
    for(unsigned int i = 0; i < soundsDeq.size();)
        if(soundsDeq[i].getStatus() != sf::Sound::Playing)
            soundsDeq.erase(soundsDeq.begin() + i);
        else
            ++i;
}
