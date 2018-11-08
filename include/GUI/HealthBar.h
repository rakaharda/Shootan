#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Utils/ResourceManager.h"
#include <iostream>

using namespace std;

class HealthBar : public sf::Drawable
{
public:
    HealthBar(Player* _player);
    virtual ~HealthBar();
    void update();
protected:
private:
    Player* player;
    sf::Sprite frame;
    sf::Sprite healthCells;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;
extern ResourceManager  *resources;
#endif // HEALTHBAR_H
