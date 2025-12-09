#pragma once
#ifndef MATCH_HPP
#define MATCH_HPP

#include "Scene.hpp"
#include "Player.hpp"

class match : public scene {
private:
    player m_ply;
public:
    match();
    void update(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
};

#endif