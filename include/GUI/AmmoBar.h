#ifndef PROJECTILESBAR_H
#define PROJECTILESBAR_H

#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Utils/ResourceManager.h"

class AmmoBar: public sf::Drawable
{
public:
    AmmoBar(Player* _player);
    virtual ~AmmoBar();
    void update();
private:
    Player*      player;
    sf::Sprite   clipBar;
    sf::Sprite   lineBar;
    sf::Sprite   barEdge;
    sf::Vector2f origin;
    float        clipSize;
    float        delta;
    float        reduceSpeed;
    int          numRounds;
    int          selectSkill;
    bool         isReload;
    void         updateSkill();
    void         reloadAnimate();
    void         setRect();
    void         moveToOrigin();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;
extern ResourceManager  *resources;

#endif // PROJECTILESBAR_H
