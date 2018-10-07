#include "Player.h"

Player::Player()
{
    sf::Texture texture;
    texture.loadFromFile("./data/player/sprite.png");
    m_sprite.setTexture(texture);
}

Player::~Player()
{
    //dtor
}

void Player::update()
{
    
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}
