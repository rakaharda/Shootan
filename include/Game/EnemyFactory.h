#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Creatures/Enemy.h"
#include "Weapons/Weapons.h"
#include "Components/GameObject.h"
#include <vector>
#include <iostream>

using namespace std;

class EnemyFactory
{
public:
    EnemyFactory(sf::Sprite* _target, sf::IntRect _fieldSize, vector<Enemy*>* _vecEnemies);
    virtual ~EnemyFactory();
    void update();
    int getScore();
private:
    sf::Sprite*    target;
    sf::IntRect    fieldSize;
    vector<Enemy*>* vecEnemies;
    float gameTimer;
    float spawnTimer;
    float currentSpawnTimer;
    float score;
    void checkEnemies();
    void spawnEnemy();
    void increaseDifficulty();
};

extern float frameTime;
extern ResourceManager      *resources;

#endif // ENEMYFACTORY_H
