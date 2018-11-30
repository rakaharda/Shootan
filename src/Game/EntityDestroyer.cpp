#include "Game/EntityDestroyer.h"

EntityDestroyer::EntityDestroyer(Enemy* _enemyToDestroy) :
    enemyToDestroy(_enemyToDestroy),
    destroyTimer(0.3f),
    currentDestroyTimer(0.f)
{
    m_sprite.setTexture(resources->getTexture("destroyer_bar"));
    m_sprite.setTextureRect(sf::IntRect(0, 0, enemyToDestroy->m_sprite.getTexture()->getSize().y + 10, m_sprite.getTexture()->getSize().y));
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x / 2.f, m_sprite.getTexture()->getSize().y / 2.f);
    m_sprite.setPosition(enemyToDestroy->m_sprite.getPosition().x - enemyToDestroy->m_sprite.getTexture()->getSize().y / 2.f - 5.f,
                         enemyToDestroy->m_sprite.getPosition().y + enemyToDestroy->m_sprite.getTexture()->getSize().y / 2.f);
    sound.setBuffer(resources->getSoundBuffer("destroy"));
    sound.setVolume(audioSettings->sounds);
    sound.setPosition(enemyToDestroy->m_sprite.getPosition().x, enemyToDestroy->m_sprite.getPosition().y, 0.f);
    sound.setMinDistance(500);
    sound.play();
}

EntityDestroyer::~EntityDestroyer()
{
    //dtor
}

void EntityDestroyer::update()
{
    if(currentDestroyTimer < destroyTimer)
    {
        currentDestroyTimer += frameTime;
        factor = currentDestroyTimer / destroyTimer;
        m_sprite.move(0, -1 * frameTime / destroyTimer * enemyToDestroy->m_sprite.getTexture()->getSize().y);
        if(factor != 0.f)
            enemyToDestroy->m_sprite.setColor(sf::Color(255, 255, 255, 255 * (1 - factor)));
    }
    else
    {
        enemyToDestroy->toDelete = true;
        toDelete = true;
    }
}

void EntityDestroyer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
