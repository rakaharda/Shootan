#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "Components/GameObject.h"

using namespace std;

class Button: public GameObject
{
public:
    Button(string _name, string _path, float _size, float _xPos, float _yPos, std::function<void(void)> _func);
    virtual ~Button();
    void changeButtonName(string _name);
    void changeButtonSprite(string _path);
    bool isClicked(float _xPos, float _yPos);
    bool isSelect;
protected:
    sf::Texture texture;
    sf::Text text;
    sf::Font font;
    std::function <void(void)> m_function;
    int id;
private:
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;
extern float frameTime;

#endif // BUTTON_H
