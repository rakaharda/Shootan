#include "GUI/HealthBar.h"

HealthBar::HealthBar(Player* _player) :
    player(_player)
{
    frame.setTexture(resources->getTexture("healthbar_frame"));
    healthCells.setTexture(resources->getTexture("healthbar_cells"));
    frame.setPosition(50, window.getSize().y - 50);
    healthCells.setPosition(frame.getPosition());
}

HealthBar::~HealthBar()
{
    //dtor
}

void HealthBar::update()
{
    int cells;
    if(player->getCurrentHealthPoints() > 0)
        cells = 10 * player->getCurrentHealthPoints() / player->getHealthPoints();
    else
        cells = 0.f;
    healthCells.setTextureRect(sf::IntRect(0, 0, 8 + (cells * 23), healthCells.getTexture()->getSize().y));
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(healthCells, states);
}
