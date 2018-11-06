#include "Utils/ResourceManager.h"

ResourceManager::ResourceManager()
{
    textureMap.emplace("default", sf::Texture());
    textureMap["default"].loadFromFile("./data/default/default.png");
    textureMap["default"].setRepeated(true);
    fontMap.emplace("default", sf::Font());
    fontMap["default"].loadFromFile("./data/fonts/arial.ttf");
    soundBufferMap.emplace("default", sf::SoundBuffer());
    soundBufferMap["default"].loadFromFile("./data/sounds/default.wav");
    musicMap.emplace("default", new sf::Music());
    musicMap["default"]->openFromFile("./data/sounds/default.wav");
}

//* Textures
void ResourceManager::addTexture(string _key, string _path)
{
    textureMap.emplace(_key, sf::Texture());
    if(!textureMap[_key].loadFromFile(_path))
    {
        textureMap[_key].loadFromFile("./data/default/default.png");
    }
    textureMap[_key].setSmooth(true);
}

void ResourceManager::addTexture(string _key, string _path, bool _repeated)
{
    addTexture(_key, _path);
    textureMap[_key].setRepeated(_repeated);
}

sf::Texture& ResourceManager::getTexture(string _key)
{
    if(textureMap.find(_key) != textureMap.end())
        return textureMap[_key];
    else
        return textureMap["default"];
}

void ResourceManager::deleteTexture(string _key)
{
    textureMap.erase(_key);
}

//* Fonts
void ResourceManager::addFont(string _key, string _path)
{
    fontMap.emplace(_key, sf::Font());
    if(!fontMap[_key].loadFromFile(_path))
    {
        fontMap[_key].loadFromFile("./data/fonts/arial.ttf");
    }
}

void ResourceManager::deleteFont(string _key)
{
    fontMap.erase(_key);
}

sf::Font& ResourceManager::getFont(string _key)
{
    if(fontMap.find(_key) != fontMap.end())
        return fontMap[_key];
    else
        return fontMap["default"];
}

//* SoundBuffers
void ResourceManager::addSoundBuffer(string _key, string _path)
{
    soundBufferMap.emplace(_key, sf::SoundBuffer());
    if(!soundBufferMap[_key].loadFromFile(_path))
    {
        soundBufferMap[_key].loadFromFile("./data/sounds/default.wav");
    }
}

void ResourceManager::deleteSoundBuffer(string _key)
{
    soundBufferMap.erase(_key);
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(string _key)
{
    if(soundBufferMap.find(_key) != soundBufferMap.end())
        return soundBufferMap[_key];
    else
        return soundBufferMap["default"];
}

//* Music
void ResourceManager::addMusic(string _key, string _path)
{
    musicMap.emplace(_key, new sf::Music());
    if(!musicMap[_key]->openFromFile(_path))
    {
        musicMap[_key]->openFromFile("./data/sounds/default.wav");
    }
}

void ResourceManager::deleteMusic(string _key)
{
    musicMap.erase(_key);
}

sf::Music* ResourceManager::getMusic(string _key)
{
    if(musicMap.find(_key) != musicMap.end())
        return musicMap[_key];
    else
        return musicMap["default"];
}
