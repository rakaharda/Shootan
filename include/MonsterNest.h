#ifndef MONSTERNEST_H
#define MONSTERNEST_H

#include "Enemy.h"
#include "Monster.h"

class MonsterNest : public Enemy
{
    public:
        MonsterNest(int _xPos, int _yPos, const sf::Sprite* _sprite, float _healthPoints);
        virtual ~MonsterNest(){};
        virtual void update();
    protected:
        void loadTexture();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


extern float frameTime;
extern vector <Enemy*> vecEnemies;
extern vector <sf::Texture> vecTextures;
#endif // MONSTERNEST_H
