#ifndef BUTTON_H
#define BUTTON_H


#include "GameObject.h"

using namespace std;

class Button: public GameObject
{
    public:
        Button(string *_str,float _xPos, float _yPos, int _id);
        virtual ~Button();
        void setID(int _id);
        int getId();
    private:
        sf::Texture texture;
        sf::Text text;
        int id;

};

#endif // BUTTON_H
