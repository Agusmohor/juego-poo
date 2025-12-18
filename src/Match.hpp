#pragma once
#ifndef MATCH_HPP
#define MATCH_HPP

#include "Scene.hpp"
#include "Player.hpp"
#include "Hud.hpp"
#include <SFML/System/Clock.hpp>

class match : public scene {
private:
    player m_ply;
    sf::Texture m_text;
    sf::Sprite Fondo;
    sf::View m_view,m_uiview;
    sf::Vector2u m_winSize;
    sf::Clock timer;
    hud m_hud;
public:
    match();
    void doPause(Game &m_gam);
    void update(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void render(sf::RenderWindow &m_win);
    void mouseSkin(sf::RenderWindow &m_win);
};

#endif