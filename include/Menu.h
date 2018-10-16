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
    private:
        void processEvents();
        void searchButton();
        virtual void startProcess(int _id);
        vector <Button*> buttons;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

extern sf::RenderWindow window;
extern float frameTime;

#endif // MENU_H
