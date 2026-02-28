#pragma once

#include <SFML/Graphics.hpp>
#include "gameplay/Stats.hpp"
#include "core/Drawble.hpp"

class obstacle : public drawble {
protected:
    sf::Texture texture;
    sf::Sprite m_spr;
    sf::RectangleShape m_hitbox;
public:
    obstacle() : m_spr(texture){}
    virtual ~obstacle() = default;
    virtual void update() = 0;
    virtual void setPos(sf::Vector2f pos) {};
    virtual treeSave getSaves() const = 0;
    virtual sf::FloatRect getHitbox() = 0;

    virtual void random(const sf::Texture &arbol, const sf::Texture &arbol2, const sf::Texture &arbol3) {};


};

