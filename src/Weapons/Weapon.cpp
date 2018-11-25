#include "Weapons/Weapon.h"

Weapon::Weapon(sf::Sprite* _source) :
    Cooldown(0.4f),
    source(_source),
    reloadTime(3.f),
    currentReloadTime(0.f),
    clipSize(12),
    currentClipSize(clipSize),
    damage(20.f),
    spread(6),
    skill(0),
    projectileSpeed(1.f),
    wAttackDistance(40.f),
    textureKey("projectile_1"),
    shotSoundKey("pistol_shot"),
    reloadSoundKey("pistol_reload")
{

}

void Weapon::update()
{
    reduceCooldown();
    if(currentReloadTime >= 0.f)
        currentReloadTime -= frameTime;
    if(sounds.size() != 0)
        if(sounds.front().getStatus() != sf::Sound::Playing)
            sounds.pop_front();
}

bool Weapon::addProjectile()
{
    if(currentCooldown <= 0.f && currentReloadTime <= 0.f && currentClipSize > 0)
    {
        currentClipSize--;
        currentCooldown = weaponCooldown;
        vecProjectiles.push_back(new Projectile(source, damage, spread, resources->getTexture(textureKey), projectileSpeed, skill));
        playShotSound();
        return true;
    }
    if(currentClipSize <= 0)
    {
        playReloadSound();
        currentReloadTime = reloadTime;
        currentClipSize = clipSize;
    }
    return false;
}

void Weapon::reload()
{
    playReloadSound();
    currentReloadTime = reloadTime;
    currentClipSize = clipSize;
}

float Weapon::getReloadTime()
{
    return reloadTime;
}

void Weapon::setReloadTime(float _reloadTime)
{
    reloadTime = _reloadTime;
}

float Weapon::getProjectileSpeed()
{
    return projectileSpeed;
}

void Weapon::setProjectileSpeed(float _projectileSpeed)
{
    projectileSpeed = _projectileSpeed;
}

float Weapon::getCurrentReloadTime()
{
    return currentReloadTime;
}

int Weapon::getClipSize()
{
    return clipSize;
}
int Weapon::getCurrentClipSize()
{
    return currentClipSize;
}
float Weapon::getAttackDistance()
{
    return wAttackDistance;
}
void Weapon::setSkill(int _skill)
{
    skill = _skill;
}

float Weapon::getDamage()
{
    return damage;
}

void Weapon::setDamage(float _damage)
{
    damage = _damage;
}

void Weapon::playShotSound()
{
    sounds.push_back(sf::Sound());
    sounds.back().setBuffer(resources->getSoundBuffer(shotSoundKey));
    sounds.back().setPosition(source->getPosition().x, source->getPosition().y, 0.f);
    sounds.back().setMinDistance(500);
    sounds.back().play();
}
void Weapon::playReloadSound()
{
    sounds.push_back(sf::Sound());
    sounds.back().setBuffer(resources->getSoundBuffer(reloadSoundKey));
    sounds.back().setPosition(source->getPosition().x, source->getPosition().y, 0.f);
    sounds.back().setMinDistance(50);
    sounds.back().play();
}


const sf::Sprite* Weapon::getSource()
{
    return source;
}
