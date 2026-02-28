#pragma once

#include <SFML/Graphics.hpp>

#include "Drawble.h"

class obstacle : public drawble {
    public:
    virtual ~obstacle() = default;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &m_win) = 0;
    virtual void setPos(sf::Vector2f pos) = 0;
    virtual treeSave getSaves() const = 0;
    virtual sf::FloatRect getHitbox() = 0;

    virtual void random(const sf::Texture &arbol, const sf::Texture &arbol2, const sf::Texture &arbol3) = 0;


};

