#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class entity{
public:
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& m_win) = 0;
    virtual void texture() = 0;
    virtual ~entity() = default;
};

#endif