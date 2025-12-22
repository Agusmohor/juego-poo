#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "Hud.hpp"
#include <SFML/System/Clock.hpp>
#include "Zombie.h"
#include "Mapa.h"

class match : public scene {
    mapa m_mapa;

    player m_ply;

    zombie m_zombie;

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
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void render(sf::RenderWindow &m_win);
    void mouseSkin(const sf::RenderWindow &m_win);


    void normalView(sf::RenderWindow& m_win);


};
