#include "ProjectilesBar.h"

ProjectilesBar::ProjectilesBar(Player* _player)
{
    clipBar.setTexture(resources->getTexture("projectiles_scale"));
    origin = sf::Vector2f(window.getSize().x - 50 - clipBar.getTexture()->getSize().x, window.getSize().y - 100);
    moveToOrigin();
}

ProjectilesBar::~ProjectilesBar()
{
    //dtor
}

void ProjectilesBar::update()
{
    cout << 1 << endl;
    float clipSize = (float)(player->getWeapon()->getCurrentClipSize())/(float)(player->getWeapon()->getClipSize());
    cout << clipSize << endl;
    clipBar.setTextureRect(sf::IntRect(0, 0, 5 + (clipBar.getTexture()->getSize().x * clipSize),
                                                  clipBar.getTexture()->getSize().y));
}

void ProjectilesBar::moveToOrigin()
{
    clipBar.setPosition(origin);
}

void ProjectilesBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(clipBar, states);
}
