#include "GUI/LvlBar.h"

LvlBar::LvlBar()
{
    frame.setTexture(resources->getTexture("lvlbar_frame"));
    lvlCells.setTexture(resources->getTexture("lvlbar_cells"));
    origin = sf::Vector2f(50, window.getSize().y - 120);
    moveToOrigin();
    currentMaxScore = 0;
    animationLvl = false;
}

LvlBar::~LvlBar()
{
    //
}

void LvlBar::update(int score, int nextscore)
{

    if(nextscore != currentMaxScore)
    {
        currentScore = currentMaxScore;
        animationLvl = true;
        moduleScore = nextscore - currentMaxScore;
        currentMaxScore = nextscore;
    }
    lvlCells.setTextureRect(sf::IntRect(0, 0, (246 * (score - currentScore)) / moduleScore, lvlCells.getTexture()->getSize().y));
}

void LvlBar::moveToOrigin()
{
    frame.setPosition(origin);
    lvlCells.setPosition(origin);
}

void LvlBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
    target.draw(lvlCells, states);
}
