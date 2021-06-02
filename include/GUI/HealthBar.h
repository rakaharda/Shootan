#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/Graphics.hpp>
#include "Player/Player.h"
#include "Utils/ResourceManager.h"
#include "GUI/StatusBar.h"
#include <iostream>

using namespace std;

class HealthBar : public StatusBar
{
public:
    HealthBar(Player* _player);
    virtual ~HealthBar();
    void update();
protected:
private:
    Player*      player;
    sf::Sprite   healthCells;
    float        amplitude;
    float        prevHealthPoints;
    float        currentHealthPoints;
    unsigned int prevWindowsHeight;
    bool         isDamaged;
    bool         direction;
    void         shake();
    void         moveToOrigin();
    void         move(float _x);
    void         updateOrigin();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;
extern ResourceManager  *resources;
#endif // HEALTHBAR_H
