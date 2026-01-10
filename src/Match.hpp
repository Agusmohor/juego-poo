#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "Hud.hpp"
#include <SFML/System/Clock.hpp>
#include "Zombie.h"
#include "Mapa.hpp"
#include "Tree.hpp"

class match : public scene {
    mapa m_mapa;

    player m_ply;

    zombie m_zombie;

    sf::Texture m_text;
    sf::Sprite Fondo;

    std::vector<tree> m_trees;
    std::vector<sf::Sprite*> m_wordlSprites;


    sf::View m_view,m_uiview;
    sf::Vector2u m_winSize;
    sf::Clock timer,time;
    hud m_hud;


public:
    match();
    void doPause(Game &m_gam);
    void update(float delta,Game &m_gam) override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &m_win) override;
    void render(sf::RenderWindow &m_win);
    void mouseSkin(const sf::RenderWindow &m_win);
    bool attact(sf::RenderWindow &m_win,sf::FloatRect entpos);

    void normalView(sf::RenderWindow& m_win);


};
