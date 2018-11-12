#ifndef SLIDER_H
#define SLIDER_H

#include "Utils/ResourceManager.h"
#include "Components/GameObject.h"
#include <functional>

class Slider: public GameObject
{
public:
    Slider(string _name, float _xPos, float _yPos, float _status);
    bool isPressed(float _xPos, float _yPos);
    bool pressed;
    virtual ~Slider();
private:
    float status;
    sf::Sprite lineSprite;
    sf::Text text;
    std::function <void(float)> m_function;
    void setFunction(std::function <void(float)> _function);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow     window;
extern ResourceManager *resources;

#endif // SLIDER_H
