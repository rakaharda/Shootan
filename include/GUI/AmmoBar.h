#ifndef PROJECTILESBAR_H
#define PROJECTILESBAR_H

#include <SFML/Graphics.hpp>
#include "GUI/StatusBar.h"
#include "Player/Player.h"
#include "Utils/ResourceManager.h"

class AmmoBar: public StatusBar
{
public:
    AmmoBar(Player* _player);
    virtual ~AmmoBar();
    void update();
private:
    Player*      player;
    float        clipSize;
    float        delta;
    float        reduceSpeed;
    int          numRounds;
    int          selectSkill;
    bool         isReload;
    void         updateSkill();
    void         reloadAnimate();
    void         setRect();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;
extern ResourceManager  *resources;

#endif // PROJECTILESBAR_H
