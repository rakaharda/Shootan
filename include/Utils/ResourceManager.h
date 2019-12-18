#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <map>

using namespace std;

class ResourceManager
{
public:
    ResourceManager();
    virtual ~ResourceManager() {};
    //* Texture
    void addTexture(string _key, string _path);
    void addTexture(string _key, string _path, bool _repeated);
    void deleteTexture(string _key);
    sf::Texture& getTexture(string _key);
    //* Font
    void addFont(string _key, string _path);
    void deleteFont(string _key);
    sf::Font& getFont(string _key);
    //* Sound buffer
    void addSoundBuffer(string _key, string _path);
    void deleteSoundBuffer(string _key);
    sf::SoundBuffer& getSoundBuffer(string _key);
    //* Music
    void addMusic(string _key, string _path);
    void deleteMusic(string _key);
    sf::Music* getMusic(string _key);
protected:
    map<string, sf::Texture> textureMap;
    map<string, sf::SoundBuffer> soundBufferMap;
    map<string, sf::Font> fontMap;
    map<string, sf::Music*> musicMap;
private:

};

#endif // RESOURCEMANAGER_H
