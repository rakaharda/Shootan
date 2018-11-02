#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>

using namespace std;

class ResourceManager
{
    public:
        ResourceManager();
        virtual ~ResourceManager();
        void addTexture(string _key, string _path);
        void addTexture(string _key, string _path, bool _repeated);
        sf::Texture& getTexture(string _key);
    protected:
        map<string, sf::Texture> textureMap;
        map<string, sf::SoundBuffer> soundBufferMap;
        map<string, sf::Font> fontMap;
    private:
    
};

#endif // RESOURCEMANAGER_H
