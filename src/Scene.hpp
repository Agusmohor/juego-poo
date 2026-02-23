#pragma once
#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>

class Game;

struct stats {
    float timeAlive = 0.f;
    int kills = 0;
};

class scene{
public:
    virtual ~scene() = default;
    virtual void update(float delta,Game &m_gam) = 0;
    virtual void updateView(Game &m_gam) = 0;
    virtual void draw(sf::RenderWindow &m_win) = 0;
};

#endif