#pragma once

#include "Scene.hpp"
#include "Player.hpp"
#include "Hud.hpp"
#include <SFML/System/Clock.hpp>
#include "Zombie.h"
#include "Mapa.hpp"
#include "obstacle.h"
#include "Tree.hpp"

class match : public scene {
    mapa m_mapa;

    std::unique_ptr<player> m_ply;

    std::unique_ptr<zombie> m_zombie;

    sf::Texture m_text;
    sf::Sprite Fondo;

    //vector de obstaculos para agregar arboles,rocas,etc
    std::vector<std::unique_ptr<obstacle>> m_obtacles;
    std::vector<sf::FloatRect> m_hitboxes;
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
