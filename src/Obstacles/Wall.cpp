#include "Obstacles/Wall.h"

Wall::Wall(int _xPos, int _yPos, int rot) : Obstacles()
{
    passability = false;
    m_sprite.setTexture(resources->getTexture("obstacles_wall"));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2, m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setPosition(_xPos, _yPos);
    float angle;
    switch(rot)
    {
        case 0: angle = 0.f; break;
        case 1: angle = 45.f; break;
        case 2: angle = 90.f; break;
        case 3: angle = 135.f; break;
        default: angle = 0.f; break;
    }

    m_sprite.setRotation(angle);
}
void Wall::smash(Player* &players)
{
    players->recline(10, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(-20, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(10, 10);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(0, -20);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(10, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(0, 20);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(-20, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(0, 20);
    if(!checkCollision(players, this))
    {
        return;
    }
}

void Wall::smash(PlayerClient* &players)
{
    players->recline(10, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(-20, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(10, 10);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(0, -20);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(10, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(0, 20);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(-20, 0);
    if(!checkCollision(players, this))
    {
        return;
    }
    players->recline(0, 20);
    if(!checkCollision(players, this))
    {
        return;
    }
}
