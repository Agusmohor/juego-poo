#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Mapa.hpp"
#include <SFML/Graphics.hpp>

class entity{
public:
    virtual void update(float delta,mapa &mapa) = 0;
    virtual void draw(sf::RenderWindow& m_win) = 0;
    virtual sf::Sprite& getSprite() = 0;

    virtual void texture() = 0;
    virtual void move(float delta,mapa &mapa) = 0;
    virtual int manyLife() = 0;
    virtual bool isAlive() = 0;
    virtual bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos) = 0;
    virtual void RecieveDamage() = 0;
    virtual sf::FloatRect getHitbox() = 0;
    virtual ~entity() = default;
};

#endif