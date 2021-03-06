#include "GUI/PerkMenu.h"
#include <iostream>

PerkMenu::PerkMenu(SurvivalStates *_survivalState, Player** _player):
    maxHP(5),
    currentHP(0),
    maxSpeed(5),
    currentSpeed(0),
    maxImprovementWeapon(5),
    currentImprovementWeapon(0),
    maxFire(5),
    currentFire(0),
    maxFrost(5),
    currentFrost(0),
    LVL(0),
    currentlvl(1),
    lvlScore(500)
{
    nextlvl = 1000;
    player = *_player;
    weapon = player->getWeapon();
    survivalState = _survivalState;
    setFunctions();
    string str[6];
    str[5] = "perkmenu_buttonPlay";
    str[0] = "perkmenu_buttonHP";
    str[1] = "perkmenu_buttonSpeedUp";
    str[2] = "perkmenu_buttonImprovementWeapon";
    str[3] = "perkmenu_buttonFrost";
    str[4] = "perkmenu_buttonFire";
    loadResources();
    info.setFont(resources->getFont("arial"));
    info.setFillColor(sf::Color::Red);
    for(int i = 0; i < 5; i++)
    {
        buttons.push_back(new Button(resources->getTexture(str[i]), window.getSize().x/2 - 260 + (i * 130), window.getSize().y/2));
        buttons.back()->setFunction(buttonFunctions[i]);
        buttons.back()->setLightButton(str[i]+"Light");
    }
    for(int i = 0; i < 6; i++)
        str[i].erase();
    backGroundSprite.setTexture(resources->getTexture("perkmenu_background"));
    backGroundSprite.setPosition(window.getSize().x/2 - backGroundSprite.getTexture()->getSize().x / 2,
                                 window.getSize().y/2 - backGroundSprite.getTexture()->getSize().y / 2);
}

PerkMenu::~PerkMenu()
{
    buttons.clear();
}

void PerkMenu::loadResources()
{
    resources->addTexture("perkmenu_buttonPlay",    "./data/GUI/perkMenu/buttonPlay.png");
    resources->addTexture("perkmenu_buttonHP",      "./data/GUI/perkMenu/buttonHP.png");
    resources->addTexture("perkmenu_buttonFire",    "./data/GUI/perkMenu/buttonFire.png");
    resources->addTexture("perkmenu_buttonFrost",   "./data/GUI/perkMenu/buttonFrost.png");
    resources->addTexture("perkmenu_buttonImprovementWeapon",   "./data/GUI/perkMenu/buttonImprovementWeapon.png");
    resources->addTexture("perkmenu_buttonSpeedUp", "./data/GUI/perkMenu/buttonSpeedUp.png");
    resources->addTexture("perkmenu_background",    "./data/GUI/perkMenu/background.png");

    resources->addTexture("maxPerkmenu_buttonHP",      "./data/GUI/perkMenu/maxButtonHP.png");
    resources->addTexture("maxPerkmenu_buttonFire",    "./data/GUI/perkMenu/maxButtonFire.png");
    resources->addTexture("maxPerkmenu_buttonFrost",   "./data/GUI/perkMenu/maxButtonFrost.png");
    resources->addTexture("maxPerkmenu_buttonImprovementWeapon",   "./data/GUI/perkMenu/maxButtonImprovementWeapon.png");
    resources->addTexture("maxPerkmenu_buttonSpeedUp", "./data/GUI/perkMenu/maxButtonSpeedUp.png");

    resources->addTexture("perkmenu_buttonHPLight",      "./data/GUI/perkMenu/buttonHPLight.png");
    resources->addTexture("perkmenu_buttonFireLight",    "./data/GUI/perkMenu/buttonFireLight.png");
    resources->addTexture("perkmenu_buttonFrostLight",   "./data/GUI/perkMenu/buttonFrostLight.png");
    resources->addTexture("perkmenu_buttonImprovementWeaponLight",   "./data/GUI/perkMenu/buttonImprovementWeaponLight.png");
    resources->addTexture("perkmenu_buttonSpeedUpLight", "./data/GUI/perkMenu/buttonSpeedUpLight.png");
}

void PerkMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [6];
    buttonFunctions[5] = [this](){
//        *menuStatus = false;
    };
    buttonFunctions[0] = [this](){
        if((currentHP < maxHP) && (LVL > 0))
        {
            LVL--;
            buttons[0]->setlvl(currentHP + 1);
            if(currentHP == 4)
            {
                buttons[0]->setTextureButton(resources->getTexture("maxPerkmenu_buttonHP"));
                buttons[0]->setLightButton("maxPerkmenu_buttonHP");
                buttons[0]->setlvl(0);
            }
            currentHP++;
            player->setHealthPoints(player->getHealthPoints() + 50);
            player->setCurrentHealthPoints(player->getHealthPoints());
            *survivalState = SurvivalStates::SS_PLAY;
        }
    };
    buttonFunctions[1] = [this](){
        if((currentSpeed < maxSpeed) && (LVL > 0))
        {
            LVL--;
            buttons[1]->setlvl(currentSpeed + 1);
            if(currentSpeed == 4)
            {
                buttons[1]->setTextureButton(resources->getTexture("maxPerkmenu_buttonSpeedUp"));
                buttons[1]->setLightButton("maxPerkmenu_buttonSpeedUp");
                buttons[1]->setlvl(0);
            }
            currentSpeed++;
            if(player->getSpeed() != player->getDefaultSpeed())
            {
                player->setSpeed(player->getSpeed() - player->getSpeedUp());
                player->setSpeedUp(player->getSpeedUp() + 20.f);
                player->setSpeed(player->getSpeed()+ player->getSpeedUp());
            }
            else
            player->setSpeedUp(player->getSpeedUp() + 20.f);
            player->setDefaultSpeed(player->getDefaultSpeed() + 20.f);
            player->setSpeed(player->getSpeed() + 20.f);
            *survivalState = SurvivalStates::SS_PLAY;
        }
    };
    buttonFunctions[2] = [this](){
        if((currentImprovementWeapon < maxImprovementWeapon) && (LVL > 0))
        {
            LVL--;
            buttons[2]->setlvl(currentImprovementWeapon + 1);
            if(currentImprovementWeapon == 4)
            {
                buttons[2]->setTextureButton(resources->getTexture("maxPerkmenu_buttonImprovementWeapon"));
                buttons[2]->setLightButton("maxPerkmenu_buttonImprovementWeapon");
                buttons[2]->setlvl(0);
            }
            currentImprovementWeapon++;
            player->updatePerkWeapon();
            *survivalState = SurvivalStates::SS_PLAY;
        }

    };
    buttonFunctions[3] = [this](){
        if((currentFrost < maxFrost) && (LVL > 0))
        {
            LVL--;
            buttons[3]->setlvl(currentFrost + 1);
            if(currentFrost == 4)
            {
                buttons[3]->setTextureButton(resources->getTexture("maxPerkmenu_buttonFrost"));
                buttons[3]->setLightButton("maxPerkmenu_buttonFrost");
                buttons[3]->setlvl(0);
            }
            currentFrost++;
            Enemy::FrostRotationRate = 90.f - (currentFrost * 20.f - ((currentFrost - 2) * 10.f));
            Enemy::FrostSpeed = 150.f - (currentFrost * 20.f - ((currentFrost - 2) * 10.f));
            player->setSkill(2);
            *survivalState = SurvivalStates::SS_PLAY;
        }

    };
    buttonFunctions[4] = [this](){
        //Perk Fire++
        if((currentFire < maxFire) && (LVL > 0))
        {
            LVL--;
            buttons[4]->setlvl(currentFire + 1);
            if(currentFire == 4)
            {
                buttons[4]->setTextureButton(resources->getTexture("maxPerkmenu_buttonFire"));
                buttons[4]->setLightButton("maxPerkmenu_buttonFire");
                buttons[4]->setlvl(0);
            }
            currentFire++;
            Enemy::percentDamage = currentFire * 0.05;
            player->setSkill(1);
            *survivalState = SurvivalStates::SS_PLAY;
        }

    };
}

void PerkMenu::update()
{
    
}

void PerkMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backGroundSprite, states);
    target.draw(info, states);
    for(unsigned int i = 0; i < buttons.size(); i++)
        target.draw(*buttons[i], states);
}

void PerkMenu::updatelvl(int _score)
{
    while(_score >= lvlScore + 500 * currentlvl)
    {
        LVL++;
        currentlvl++;
        lvlScore += 500 * currentlvl;
        nextlvl = lvlScore + 500 * currentlvl;
    }
    checkWeapon();
}

void PerkMenu::checkWeapon()
{
    if(weapon!=player->getWeapon())
    {
        for(unsigned int i = 0; i < currentImprovementWeapon; i++)
            player->updatePerkWeapon();
        weapon = player->getWeapon();
    }
}
void PerkMenu::handleEvents(sf::Event event)
{
    for(unsigned int i = 0; i < buttons.size(); i++)
        buttons[i]->update();
    switch(event.type)
    {
    case sf::Event::MouseButtonPressed:
        switch(event.mouseButton.button)
        {
        case sf::Mouse::Left:
            searchButton();
            break;
        default:
            break;
        }
    default:
        break;
    }
}

int PerkMenu::getlvl()
{
    return LVL;
}
int PerkMenu::getnextlvl()
{
    return nextlvl;
}
bool PerkMenu::canOpen()
{
    if((currentFire == maxFire) && (currentFrost == maxFrost) && (currentSpeed == maxSpeed) && (currentImprovementWeapon == maxImprovementWeapon) && (currentHP == maxHP))
        return 0;
    else
        return 1;
}
