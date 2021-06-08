#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <deque>
#include "SFML/Audio.hpp"

class SoundManager
{
    public:
        SoundManager();
        ~SoundManager();
        void addSound(sf::SoundBuffer soundBuffer, float volume = 100.f, float posX = 0.f, float posY = 0.f, float minDistance = 0.f);
    protected:
    std::deque<sf::Sound> soundsDeq;
    void clearDeq();
    private:
};

#endif // SOUNDMANAGER_H
