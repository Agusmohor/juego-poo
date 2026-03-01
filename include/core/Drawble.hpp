#ifndef JUEGO_POO_DRAWBLE_H
#define JUEGO_POO_DRAWBLE_H
#include "SFML/Graphics.hpp"

class drawble {
protected:
    sf::RectangleShape hitbox;
public:
    virtual void draw(sf::RenderWindow& win) {};
    virtual const sf::Vector2f getPosition() const {return sf::Vector2f(0,0);};
    virtual const sf::FloatRect getGlobalBounds() const {return sf::FloatRect();};
    virtual void drawHitbox(sf::RenderWindow &m_win){m_win.draw(hitbox);};
};

#endif