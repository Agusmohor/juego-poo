#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include "world/Player.hpp"

class hud{
    sf::Texture gui;
    sf::Sprite life, m_shield, m_dash, m_fire, m_heal, overlay;
    sf::Vector2f scale,pos,spos,abilPos, overlayPos, newPos;
    std::vector<sf::Sprite> hp_empty,hp_fill,stamina_bar,stamina_empty, m_overlay;
    sf::Vector2i size;

    sf::Font font;
    sf::Text text;

    sf::Clock timer;

    sf::Color stamColor;

    bool isDead = false;
    bool stamTaked = false;
    int stamPart = 1;
    bool state, isStaminaEmpty;
    int  playerHp,playerStam;

    void create();
    void caseHealth();
    void caseStamina();

    void deathMessege(sf::RenderWindow &m_win);
    void createLife(int num);
    void createStamina(int num);
    void abilities(bool isShieldReady, bool isDashReady, bool isFireReady, bool isHealReady);

public:
    hud();
    void update();
    void updateView();
    void draw(sf::RenderWindow &m_win);
    void onResize(const sf::Vector2f &newView);
    void ProcessEvent(game& game,sf::Event &event);

    void checkPlayer(const player& p);

};

#endif