#include "GUI/PerkMenu.h"
#include <iostream>

PerkMenu::PerkMenu(bool *_menuStatus, Player** _player):
    maxHP(5),
    currentHP(0),
    maxSpeed(5),
    currentSpeed(0),
    maxPlayerSpeed(5),
    currentPlayerSpeed(0),
    maxFire(5),
    currentFire(0),
    maxFrost(5),
    currentFrost(0),
    LVL(0),
    currentlvl(0)
{
    player = *_player;
    menuStatus = _menuStatus;
    setFunctions();
    string str[6];
    str[0] = "perkmenu_buttonPlay";
    str[1] = "perkmenu_buttonHP";
    str[2] = "perkmenu_buttonSpeedUp";
    str[3] = "perkmenu_buttonSpeed";
    str[4] = "perkmenu_buttonFrost";
    str[5] = "perkmenu_buttonFire";
    loadResources();
    info.setFont(resources->getFont("arial"));
    info.setFillColor(sf::Color::Red);
    for(int i = 0; i < 6; i++)
    {
        buttons.push_back(new Button(resources->getTexture(str[i]), window.getSize().x/2 - 200 + (i * 80), window.getSize().y/2));
        buttons.back()->setFunction(buttonFunctions[i]);
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
    resources->addTexture("perkmenu_buttonSpeed",   "./data/GUI/perkMenu/buttonSpeed.png");
    resources->addTexture("perkmenu_buttonSpeedUp", "./data/GUI/perkMenu/buttonSpeedUp.png");
    resources->addTexture("perkmenu_background",    "./data/GUI/perkMenu/background.png");

    resources->addTexture("maxPerkmenu_buttonPlay",    "./data/GUI/perkMenu/maxButtonPlay.png");
    resources->addTexture("maxPerkmenu_buttonHP",      "./data/GUI/perkMenu/maxButtonHP.png");
    resources->addTexture("maxPerkmenu_buttonFire",    "./data/GUI/perkMenu/maxButtonFire.png");
    resources->addTexture("maxPerkmenu_buttonFrost",   "./data/GUI/perkMenu/maxButtonFrost.png");
    resources->addTexture("maxPerkmenu_buttonSpeed",   "./data/GUI/perkMenu/maxButtonSpeed.png");
    resources->addTexture("maxPerkmenu_buttonSpeedUp", "./data/GUI/perkMenu/maxButtonSpeedUp.png");
}

void PerkMenu::setFunctions()
{
    buttonFunctions = new std::function<void(void)> [6];
    buttonFunctions[0] = [this](){
        *menuStatus = false;
    };
    buttonFunctions[1] = [this](){
        //HP++
        if((currentHP < maxHP) && (LVL > 0))
        {
            LVL--;
            buttons[1]->setlvl(currentHP + 1);
            if(currentHP == 4)
            {
                buttons[1]->setTextureButton(resources->getTexture("maxPerkmenu_buttonHP"));
                buttons[1]->setlvl(0);
            }
            currentHP++;
            player->setHealthPoints(player->getHealthPoints() + 50);
            player->setCurrentHealthPoints(player->getHealthPoints());
            stringstream ss;
            ss << endl << "LVL: " << LVL;
            info.setString(ss.str());
        }
    };
    buttonFunctions[2] = [this](){
        //Perk UpSpeed++
        if((currentSpeed < maxSpeed) && (LVL > 0))
        {
            LVL--;
            buttons[2]->setlvl(currentSpeed + 1);
            if(currentSpeed == 4)
            {
                buttons[2]->setTextureButton(resources->getTexture("maxPerkmenu_buttonSpeedUp"));
                buttons[2]->setlvl(0);
            }
            currentSpeed++;
            if(player->speed != player->defoltSpeed)
            {
                player->speed -= player->upSpeed;
                player->upSpeed += 30.f;
                player->speed += player->upSpeed;
            }
            else
            player->upSpeed += 30.f;
            stringstream ss;
            ss << endl << "LVL: " << LVL;
            info.setString(ss.str());

        }
    };
    buttonFunctions[3] = [this](){
        if((currentPlayerSpeed < maxPlayerSpeed) && (LVL > 0))
        {
            LVL--;
            buttons[3]->setlvl(currentPlayerSpeed + 1);
            if(currentPlayerSpeed == 4)
            {
                buttons[3]->setTextureButton(resources->getTexture("maxPerkmenu_buttonSpeed"));
                buttons[3]->setlvl(0);
            }
            currentPlayerSpeed++;
            player->defoltSpeed+=20.f;
            player->speed+=20.f;
            stringstream ss;
            ss << endl << "LVL: " << LVL;
            info.setString(ss.str());

        }

    };
    buttonFunctions[4] = [this](){
        if((currentFrost < maxFrost) && (LVL > 0))
        {
            LVL--;
            buttons[4]->setlvl(currentFrost + 1);
            if(currentFrost == 4)
            {
                buttons[4]->setTextureButton(resources->getTexture("maxPerkmenu_buttonFrost"));
                buttons[4]->setlvl(0);
            }
            currentFrost++;
            Enemy::FrostRotationRate = 90.f - (currentFrost * 20.f - ((currentFrost - 2) * 10.f));
            Enemy::FrostSpeed = 150.f - (currentFrost * 20.f - ((currentFrost - 2) * 10.f));
            player->setSkill(2);
            stringstream ss;
            ss << endl << "LVL: " << LVL;
            info.setString(ss.str());

        }

    };
    buttonFunctions[5] = [this](){
        if((currentFire < maxFire) && (LVL > 0))
        {
            LVL--;
            buttons[5]->setlvl(currentFire + 1);
            if(currentFire == 4)
            {
                buttons[5]->setTextureButton(resources->getTexture("maxPerkmenu_buttonFire"));
                buttons[5]->setlvl(0);
            }
            currentFire++;
            Enemy::percentDamage = currentFire * 0.05;
            player->setSkill(1);
            stringstream ss;
            ss << endl << "LVL: " << LVL;
            info.setString(ss.str());
        }

    };
}
void PerkMenu::handleEvents(sf::Event event)
{

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
    case sf::Event::KeyPressed:
        {
            if(event.key.code == sf::Keyboard::Escape)
            *menuStatus = false;
            break;
        }
    default:
        break;
    }
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
    while(_score >= 1000 * currentlvl)
    {
        LVL++;
        currentlvl++;
    }
    stringstream ss;
    ss << endl << "LVL: " << LVL;
    info.setString(ss.str());
}
