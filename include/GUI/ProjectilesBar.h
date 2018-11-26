#ifndef PROJECTILESBAR_H
#define PROJECTILESBAR_H

#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Utils/ResourceManager.h"

class ProjectilesBar: public sf::Drawable
{
public:
    ProjectilesBar(Player* _player);
    virtual ~ProjectilesBar();
    void update();
private:
    Player*      player;
    sf::Sprite   clipBar;
    sf::Vector2f origin;
    void         moveToOrigin();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;
extern ResourceManager  *resources;

#endif // PROJECTILESBAR_H
