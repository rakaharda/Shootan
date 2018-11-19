#ifndef SLIDER_H
#define SLIDER_H

#include "Utils/ResourceManager.h"
#include "Components/GameObject.h"
#include <functional>

class Slider: public GameObject
{
public:
    Slider(string _name, float _xPos, float _yPos, float _status);
    bool isPressed();
    bool pressed;
    void setFunction(std::function <void(float)> _function);
    virtual ~Slider();
private:
    float status;
    float index;
    sf::Sprite lineSprite;
    sf::Sprite textSprite;
    sf::Text text;
    std::function <void(float)> m_function;
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow     window;
extern ResourceManager *resources;

#endif // SLIDER_H
