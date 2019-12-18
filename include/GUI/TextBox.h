#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Utils/ResourceManager.h"
#include "Components/GameObject.h"
#include <functional>

class TextBox: public GameObject
{
public:
    TextBox(string _name, float _xPos, float _yPos);
    string getText();
    void setFunction(std::function <void(void)> _func);
    void handleEvents(sf::Event event);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    std::function <void(void)> m_function;
    sf::Sprite cursor;
    sf::Text m_text;
    sf::Clock clock;
    float size = 20;
    bool selected = false;
    bool isFlick = false;
    void setCenter();
    void moveCursor();
};

extern sf::RenderWindow window;
extern ResourceManager *resources;

#endif //TEXTBOX_H
