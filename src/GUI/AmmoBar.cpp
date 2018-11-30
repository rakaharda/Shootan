#include "GUI/AmmoBar.h"

AmmoBar::AmmoBar(Player* _player)
{
    player = _player;
    isReload = false;
    selectSkill = 0;
    frame.setTexture(resources->getTexture("projectiles_scale_default"));
    delta = frame.getTexture()->getSize().x / (float)player->getWeapon()->getClipSize();
    reduceSpeed = frame.getTexture()->getSize().x/(player->getWeapon()->getCooldown()*(float)player->getWeapon()->getClipSize());
    numRounds = player->getWeapon()->getClipSize();
    origin = sf::Vector2f(window.getSize().x - frame.getTexture()->getSize().x - 50, window.getSize().y - 100);
    moveToOrigin();
}

AmmoBar::~AmmoBar()
{

}

void AmmoBar::update()
{
    reduceSpeed = frame.getTexture()->getSize().x/(player->getWeapon()->getCooldown()*(float)player->getWeapon()->getClipSize());
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
        frame.setTexture(resources->getTexture("projectiles_scale_default"));
        break;
    case 1:
        frame.setTexture(resources->getTexture("projectiles_scale_fire"));
        break;
    case 2:
        frame.setTexture(resources->getTexture("projectiles_scale_freeze"));
        break;
    case 3:
        frame.setTexture(resources->getTexture("projectiles_scale_double"));
        break;
    default:
        break;
    }
}


void AmmoBar::setRect()
{
    float expectSize = frame.getTexture()->getSize().x * clipSize;
    if(frame.getTextureRect().width > expectSize)
        frame.setTextureRect(sf::IntRect(0, 0, frame.getTextureRect().width - reduceSpeed*frameTime,
                                            frame.getTexture()->getSize().y));
}

void AmmoBar::reloadAnimate()
{
    float reloadState = (player->getWeapon()->getReloadTime() - player->getWeapon()->getCurrentReloadTime() )/player->getWeapon()->getReloadTime();
    frame.setTextureRect(sf::IntRect(0, 0, frame.getTexture()->getSize().x * reloadState, frame.getTexture()->getSize().y));
    if (reloadState >= 1.f){
        isReload = false;
    }

}

void AmmoBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(frame, states);
}
