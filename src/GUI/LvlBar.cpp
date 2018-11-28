#include "GUI/LvlBar.h"

LvlBar::LvlBar()
{
    frame.setTexture(resources->getTexture("lvlbar_frame"));
    lvlCells.setTexture(resources->getTexture("lvlbar_cells"));
    animation.setTexture(resources->getTexture("lvlbar_animation"));
    lvlup.setTexture(resources->getTexture("lvlbar_lvlup"));
    lvlup.setPosition(300, window.getSize().y - 127);
    origin = sf::Vector2f(50, window.getSize().y - 120);
    moveToOrigin();
    currentMaxScore = 0;
    animationLvl = false;
    reloadAnimation = 0.02f;
    iAnimation = 0;
}

LvlBar::~LvlBar()
{
    //
}

void LvlBar::update(int score, int nextscore, int allScore)
{
    stringstream ss;
    ss << allScore;
    if(textScore!=ss.str())
    {
        textScore = ss.str();
        setSpriteScore();
    }
    if(nextscore != currentMaxScore)
    {
        currentScore = currentMaxScore;
        if(currentMaxScore)
            animationLvl = true;
        moduleScore = nextscore - currentMaxScore;
        currentMaxScore = nextscore;
    }
    if(!animationLvl)
        lvlCells.setTextureRect(sf::IntRect(0, 0, (246 * (score - currentScore)) / moduleScore, lvlCells.getTexture()->getSize().y));
    else
    {
        if(iAnimation <=25)
        {
            if(reloadAnimation <= 0.f)
            {
                reloadAnimation = 0.02f;
                iAnimation++;
                animation.setPosition(55 + iAnimation * 8.16, window.getSize().y - 120);
            }
        }
        else
        {
            iAnimation = 0;
            animationLvl = false;
        }
        reloadAnimation -= frameTime;
    }
}

void LvlBar::setSpriteScore()
{
    spriteScore.clear();
    string num = "score_number_";
    for(unsigned int i = 0; i < textScore.size(); i++)
    {
        spriteScore.push_back(new sf::Sprite);
        spriteScore.back()->setTexture(resources->getTexture(num + textScore[i]));
        spriteScore.back()->setPosition(lvlCells.getPosition().x + lvlCells.getTexture()->getSize().x/2
        + (i - 0.5 - textScore.size()/2) * spriteScore.back()->getTexture()->getSize().x ,
        lvlCells.getPosition().y - spriteScore.back()->getTexture()->getSize().y);
    }

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
    if(animationLvl)
    {
        target.draw(lvlup, states);
        target.draw(animation, states);
    }
    for(unsigned int i = 0; i < spriteScore.size(); i++)
        target.draw(*spriteScore[i], states);
}
