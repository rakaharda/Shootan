#ifndef STUKOV_H
#define STUKOV_H

#include "Enemy.h"

class GroundExplosionSpell: public GameObject
{
public:
    GroundExplosionSpell(const sf::Sprite* _sprite);
    virtual ~GroundExplosionSpell();
    virtual void update();
    float phase;
private:
    sf::Texture texture;
    float xPos;
    float yPos;
    float castSpeed;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};


class Stukov: public Enemy
{
public:
    Stukov(int _xPos, int _yPos, const sf::Sprite* _sprite);
    virtual ~Stukov();
    virtual void update();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    /*float castTime;
    bool isCasted;
    GroundExplosionSpell m_spell; */
};


extern sf::RenderWindow window;
extern float frameTime;


#endif // STUKOV_H
