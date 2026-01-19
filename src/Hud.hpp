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

    void keyBoard();
    void moveHotbar(const sf::Vector2f &winview);

    void checkPlayer(int health,int stamina);

    void caseHealth();

    void caseStamina();

    void deathMessege(sf::RenderWindow &m_win);

private:
    void create();

    void createLife(int num);
    void createStamina(int num);

    sf::Texture hobTexture,hselTe;
    sf::Sprite hotbar, hsel, overS, life;
    sf::Keyboard::Key k_1,k_2,k_3,k_4,k_5,k_6;
    sf::Vector2f m_winSize,hselpos,scale,hpos,pos,spos;
    std::vector<sf::Sprite> hotbars,overHb,hp_empty,hp_fill,stamina_bar,stamina_empty;
    sf::Vector2i size;

    sf::Font font;
    sf::Text text;

    sf::Clock timer;
    bool isDead = false;
    bool state;
    int newpos, playerHp,playerStam;
};

#endif