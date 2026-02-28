#ifndef JUEGO_POO_DRAWBLE_H
#define JUEGO_POO_DRAWBLE_H
#include "SFML/Graphics.hpp"

class drawble {
    public:
    virtual void draw(sf::RenderWindow& win) {};
    virtual const sf::Vector2f getPosition() const {return sf::Vector2f(0,0);};
    virtual const sf::FloatRect getGlobalBounds() const {return sf::FloatRect();};
};

#endif