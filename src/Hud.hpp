#pragma once
#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>

class hud{
public:
    hud();
    void update();
    void updateView();
    void draw(sf::RenderWindow &m_win);

    void moveGui(const sf::Vector2f &winview);

    void checkPlayer(int health,int stamina, bool isStaminaEmpty);

    void caseHealth();

    void caseStamina();

    void deathMessege(sf::RenderWindow &m_win);
    void abilities(bool isShieldReady, bool isDashReady, bool isFireReady, bool isHealReady);
private:
    void create();

    void createLife(int num);
    void createStamina(int num);

    sf::Texture gui;
    sf::Sprite life, m_shield, m_dash, m_fire, m_heal, overlay;
    sf::Vector2f m_winSize,scale,pos,spos,abilPos, overlayPos;
    std::vector<sf::Sprite> hp_empty,hp_fill,stamina_bar,stamina_empty, m_overlay;
    sf::Vector2i size;

    sf::Font font;
    sf::Text text;

    sf::Clock timer;

    sf::Color stamColor;

    bool isDead = false;
    bool state, isStaminaEmpty;
    int newpos, playerHp,playerStam;
};

#endif