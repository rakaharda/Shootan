#ifndef MENU_H
#define MENU_H

#include "GUI/Button.h"
#include <vector>

using namespace std;

class Menu : public sf::Drawable
{
public:
    Menu();
    virtual ~Menu();
    virtual void handleEvents(sf::Event event);
    //virtual void update();
protected:
    void searchButton();
    virtual void setFunctions() = 0;
    vector <Button*> buttons;
    std::function<void(void)> *buttonFunctions;
    sf::Texture backGroundTexture;
    sf::Sprite backGroundSprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;

#endif // MENU_H
