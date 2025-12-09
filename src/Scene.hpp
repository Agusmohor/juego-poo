#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>

class scene{
public:
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow &m_win) = 0;
    virtual ~scene() {}
};

#endif