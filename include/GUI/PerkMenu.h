#ifndef PERKMENU_H
#define PERKMENU_H

#include "Menu.h"
#include "Game/SurvivalStates.h"
#include "Utils/ResourceManager.h"
#include "Utils/VideoSettings.h"
#include "Player/Player.h"
#include "Creatures/Enemy.h"
#include <sstream>

class PerkMenu: public Menu
{
public:
    PerkMenu(SurvivalStates *_survivalState, Player** _player);
    virtual ~PerkMenu();
    void handleEvents(sf::Event event);
    void updatelvl(int _score);
    void checkWeapon();
    void update();
    int getlvl();
    bool canOpen();
    int getnextlvl();
private:
    int maxHP;
    int currentHP;
    int maxSpeed;
    int currentSpeed;
    int maxFrost;
    int currentFrost;
    int maxFire;
    int currentFire;
    int maxImprovementWeapon;
    int currentImprovementWeapon;
    int lvlScore;
    int nextlvl;
    Player* player;
    Weapon* weapon;
    void setFunctions();
    void loadResources();
    SurvivalStates *survivalState;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    int currentlvl;
    int LVL;
    sf::Text info;
friend Button;
//    buttonFunctions;
};

extern sf::RenderWindow window;
extern ResourceManager      *resources;

#endif // PERKMENU_H
