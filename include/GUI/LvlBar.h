#ifndef LVLBAR_H
#define LVLBAR_H

#include <SFML/Graphics.hpp>
#include "Utils/ResourceManager.h"
#include "GUI/StatusBar.h"
#include "Game/GameState.h"
#include <iostream>

using namespace std;

class LvlBar : public StatusBar
{
public:
    LvlBar();
    virtual ~LvlBar();
    void update(int score, int nextscore, int allScore);
protected:
private:
    sf::Sprite   lvlCells;
    sf::Sprite   animation;
    sf::Sprite   lvlup;
    string textScore;
    vector <sf::Sprite*> spriteScore;
    int iAnimation;
    float position;
    float reloadAnimation;
    int currentMaxScore;
    int currentScore;
    int moduleScore;
    bool animationLvl;
    void setSpriteScore();
    void moveToOrigin();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float            frameTime;
extern ResourceManager  *resources;
#endif // LVLBAR_H
