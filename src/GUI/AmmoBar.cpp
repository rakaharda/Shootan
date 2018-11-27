#include "AmmoBar.h"

AmmoBar::AmmoBar(Player* _player)
{
    player = _player;
    isReload = false;
    selectSkill = 0;
    clipBar.setTexture(resources->getTexture("projectiles_scale_default"));
    lineBar.setTexture(resources->getTexture("projectiles_scale_default_line"));
    delta = clipBar.getTexture()->getSize().x / (float)player->getWeapon()->getClipSize();
    reduceSpeed = clipBar.getTexture()->getSize().x/(player->getWeapon()->getCooldown()*(float)player->getWeapon()->getClipSize());
    numRounds = player->getWeapon()->getClipSize();
    origin = sf::Vector2f(window.getSize().x - clipBar.getTexture()->getSize().x - 50, window.getSize().y - 100);
    moveToOrigin();
    lineBar.setPosition(clipBar.getPosition());
}

AmmoBar::~AmmoBar()
{

}

void AmmoBar::update()
{
    if (selectSkill!=player->getWeapon()->getSkill())
    {
        selectSkill=player->getWeapon()->getSkill();
        updateSkill();
    }
    clipSize = (float)player->getWeapon()->getCurrentClipSize()/(float)player->getWeapon()->getClipSize();
    if(player->getWeapon()->getCurrentReloadTime()>0){
        isReload = true;
    }
    if(isReload)
        reloadAnimate();
    else
        setRect();
}

void AmmoBar::updateSkill()
{
    switch(selectSkill)
    {
    case 0:
        clipBar.setTexture(resources->getTexture("projectiles_scale_default"));
        break;
    case 1:
        clipBar.setTexture(resources->getTexture("projectiles_scale_fire"));
        break;
    case 2:
        clipBar.setTexture(resources->getTexture("projectiles_scale_freeze"));
        break;
    case 3:
        clipBar.setTexture(resources->getTexture("projectiles_scale_double"));
        break;
    default:
        break;
    }
}


void AmmoBar::setRect()
{
    float expectSize = clipBar.getTexture()->getSize().x * clipSize;
    if(clipBar.getTextureRect().width > expectSize)
        clipBar.setTextureRect(sf::IntRect(0, 0, clipBar.getTextureRect().width - reduceSpeed*frameTime,
                                            clipBar.getTexture()->getSize().y));
}

void AmmoBar::reloadAnimate()
{
    float reloadState = (player->getWeapon()->getReloadTime() - player->getWeapon()->getCurrentReloadTime() )/player->getWeapon()->getReloadTime();
    clipBar.setTextureRect(sf::IntRect(0, 0, clipBar.getTexture()->getSize().x * reloadState, clipBar.getTexture()->getSize().y));
    if (reloadState >= 1.f){
        isReload = false;
    }

}

void AmmoBar::moveToOrigin()
{
    clipBar.setPosition(origin);
}

void AmmoBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(clipBar, states);
    //target.draw(barEdge, states);
    target.draw(lineBar,states);
}
