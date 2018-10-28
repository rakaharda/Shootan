#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <vector>

using namespace std;

class Menu : public sf::Drawable
{
public:
    Menu();
    virtual ~Menu();
    void processEvents(sf::Event event);
    bool *menuStatus;
protected:
    void searchButton();
    virtual void startProcess(int _id);
    vector <Button*> buttons;
    sf::Texture backGroundTexture;
    sf::Sprite backGroundSprite;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;

#endif // MENU_H
