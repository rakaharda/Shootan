#include "MonsterNest.h"

MonsterNest::MonsterNest(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints) :
    Enemy(vecTextures[2], _xPos, _yPos, _sprite, _healthPoints, 0.f)
{
    speed = 0.f;
    weaponCooldown = 5.f;
}

void MonsterNest::update()
{
    checkHealth();
    if(currentCooldown == 0.f)
    {
        vecEnemies.push_back(new Monster(m_sprite.getPosition().x+m_sprite.getTexture()->getSize().x+5,
                                         m_sprite.getPosition().y, player, 100.f, 20.f));
        currentCooldown = weaponCooldown;
    }
        reduceCooldown();
}


void MonsterNest::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
