#include "Game\EnemyFactory.h"

EnemyFactory::EnemyFactory(sf::Sprite* _target, sf::IntRect _fieldSize, vector<Enemy*>* _vecEnemies) :
    target(_target),
    fieldSize(_fieldSize),
    vecEnemies(_vecEnemies),
    gameTimer(0.f),
    spawnTimer(5.f),
    currentSpawnTimer(0.f),
    score(0.f)
{
    
}

EnemyFactory::~EnemyFactory()
{

}


void EnemyFactory::update()
{
    gameTimer += frameTime;
    if(currentSpawnTimer >= 0.f)
        currentSpawnTimer -= frameTime;
    for(unsigned int i = 0; i < vecEnemies->size(); i++)
        vecEnemies->at(i)->update();
    checkEnemies();
    spawnEnemy();
    increaseDifficulty();
}

void EnemyFactory::spawnEnemy()
{
    if(currentSpawnTimer <= 0.f)
    {
        float x;
        float y;
        switch(rand() % 4)
        {
            case 0:
                x = (float)(rand() % fieldSize.width);
                y = -100.f;
                break;
            case 1:
                x = (float)(fieldSize.width) + 100.f;
                y = (float)(rand() % fieldSize.height);
                break;
            case 2:
                x = (float)(rand() % fieldSize.width);
                y = (float)(fieldSize.height) + 100.f;
                break;
            case 3:
                x = -100.f;
                y = (float)(rand() % fieldSize.height);
                break;
            default:
                break;
        }
        switch(rand() % 10)
        {
            case 0:
                vecEnemies->push_back(new Enemy(target, 100, resources->getTexture("enemy_range")));
                vecEnemies->back()->setWeapon(new Gun(&(vecEnemies->back()->m_sprite)));
                vecEnemies->back()->getWeapon()->setDamage(10.f);
                break;
            default:
                vecEnemies->push_back(new Enemy(target, 100, resources->getTexture("enemy_melee")));
                vecEnemies->back()->setWeapon(new MeleeAttack(&(vecEnemies->back()->m_sprite)));
                break;
        }
        vecEnemies->back()->setPosition(x, y);
        currentSpawnTimer = spawnTimer;
    }
}

void EnemyFactory::increaseDifficulty()
{
    if (spawnTimer > 1.f)spawnTimer -= (spawnTimer / 1000.f) * (gameTimer / 100) * (score / 10000);
    cout<< endl << spawnTimer;
}

void EnemyFactory::checkEnemies()
{
    for(unsigned int i = 0; i < vecEnemies->size(); i++)
        if(vecEnemies->at(i)->toDelete)
        {
            score += vecEnemies->at(i)->getHealthPoints() + vecEnemies->at(i)->getWeapon()->getDamage();
            switch(rand() % 40)
            {
                case 0:
                    vecPerks.push_back(new Frost(vecEnemies->at(i)->m_sprite.getPosition().x,vecEnemies->at(i)->m_sprite.getPosition().y));
                    break;
                case 1:
                    vecPerks.push_back(new Fire(vecEnemies->at(i)->m_sprite.getPosition().x,vecEnemies->at(i)->m_sprite.getPosition().y));
                    break;
                case 2:
                    vecPerks.push_back(new Medicine(vecEnemies->at(i)->m_sprite.getPosition().x,vecEnemies->at(i)->m_sprite.getPosition().y));
                    break;
                case 3:
                    vecPerks.push_back(new UpSpeed(vecEnemies->at(i)->m_sprite.getPosition().x,vecEnemies->at(i)->m_sprite.getPosition().y));
                    break;
                default:
                    break;                
            }
            vecEnemies->erase(vecEnemies->begin() + i);
        }
}

int EnemyFactory::getScore()
{
    return (int)score;
}
