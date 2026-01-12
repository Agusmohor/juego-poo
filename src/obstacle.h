#pragma once

#include <SFML/Graphics.hpp>

class obstacle {
    public:
    virtual ~obstacle() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &m_win) = 0;

    virtual void setPos(sf::Vector2f pos) = 0;

    virtual sf::FloatRect getHitbox() = 0;

    virtual void random(const sf::Texture &arbol, const sf::Texture &arbol2, const sf::Texture &arbol3) = 0;

    virtual sf::Sprite& getSprite() = 0;

};

