#include "GUI/HealthBar.h"

HealthBar::HealthBar(Player* _player) :
    player(_player)
{
    frame.setTexture(resources->getTexture("healthbar_frame"));
    healthCells.setTexture(resources->getTexture("healthbar_cells"));
    origin = sf::Vector2f(50, window.getSize().y - 50);
    moveToOrigin();
    prevHealthPoints = 0;
    prevWindowsHeight = window.getSize().y;
    isDamaged = false;
    amplitude = 0.f;
    direction = true;
}

HealthBar::~HealthBar()
{
    //dtor
}

void HealthBar::update()
{
    int cells;
    if(prevHealthPoints != player->getCurrentHealthPoints())
    {
        if(player->getCurrentHealthPoints() > 0)
            cells = 10 * player->getCurrentHealthPoints() / player->getHealthPoints();
        else
            cells = 0.f;
        healthCells.setTextureRect(sf::IntRect(0, 0, 8 + (cells * 23), healthCells.getTexture()->getSize().y));    
        if(prevHealthPoints > player->getCurrentHealthPoints())
            isDamaged = true;
        prevHealthPoints = player->getCurrentHealthPoints();
    }
    shake();
    updateOrigin();
}

void HealthBar::shake()
{
    if(isDamaged)
    {
        amplitude = 14.f;
        isDamaged = false;
        moveToOrigin();
    }
    if(direction && (frame.getPosition().x > (origin.x + amplitude)))
    {
        direction = false;
        amplitude -= 2.f;
    }
    else if(!direction && (frame.getPosition().x < (origin.x - amplitude)))
    {
        direction = true;
        amplitude -= 2.f;
    }
    if(amplitude > 0.f)
    {
        if(direction)
            move(300 * frameTime);
        else
            move(-300 * frameTime);
    }
    
}

void HealthBar::moveToOrigin()
{
    frame.setPosition(origin);
    healthCells.setPosition(origin);
}

void HealthBar::move(float _x)
{
    frame.move(_x, 0);
    healthCells.move(_x, 0);
}

void HealthBar::updateOrigin()
{
    if(prevWindowsHeight != window.getSize().y)
    {
        prevWindowsHeight = window.getSize().y;
        origin.y = prevWindowsHeight - 50.f;
        moveToOrigin();
    }
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(healthCells, states);
}
