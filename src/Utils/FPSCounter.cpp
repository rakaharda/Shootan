#include "FPSCounter.h"

FPSCounter::FPSCounter() : counter(0)
{
    font.loadFromFile("./data/fonts/arial.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::Green);
    clock.restart();
    s = '0';
}

FPSCounter FPSCounter::operator++ ()
{
    counter++;
    return *this;
}

void FPSCounter::update()
{
    counter++;
    if (clock.getElapsedTime().asSeconds()>=0.5f)
    {
        std::stringstream ss;
        ss<<counter*2;
        s = ss.str();
        counter = 0;
        clock.restart();
    }
    text.setString(s);
}

void FPSCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(text, states);
}
