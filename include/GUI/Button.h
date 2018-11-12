#ifndef BUTTON_H
#define BUTTON_H

#include <functional>
#include "Components/GameObject.h"
#include "Utils/ResourceManager.h"

using namespace std;

class Button: public GameObject
{
public:
    Button(sf::Texture& _texture, float _xPos, float _yPos);
    virtual ~Button();
    void changeButtonSprite(sf::Texture& _texture);
    void setFunction(std::function <void()> _function);
    bool isClicked(float _xPos, float _yPos);
    bool isSelect;
    void setTextureButton(sf::Texture& _texture);
    void setlvl(int _ilvl);
protected:
    std::function <void(void)> m_function;
private:
    sf::Texture textureLvl;
    vector <sf::Sprite*>       veclvl;
    int ilvl;
    float xPos;
    float yPos;
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

extern sf::RenderWindow window;
extern float frameTime;
extern ResourceManager *resources;

#endif // BUTTON_H
