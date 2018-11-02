#include "Utils/ResourceManager.h"

ResourceManager::ResourceManager()
{
    textureMap.emplace("default", sf::Texture());
    textureMap["default"].loadFromFile("./data/default/default.png");
    textureMap["default"].setRepeated(true);
}

//* Textures
void ResourceManager::addTexture(string _key, string _path)
{
    textureMap.emplace(_key, sf::Texture());
    if(!textureMap[_key].loadFromFile(_path))
    {
        textureMap[_key].loadFromFile("./data/default/default.png");
    }
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

//TODO: Fonts

//TODO: SoundBuffers