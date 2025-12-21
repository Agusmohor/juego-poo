#pragma once
#ifndef MENU_HPP
#define MENU_HPP
#include "Scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

class menu : public scene{
public:
    menu();
    void update(Game &m_gam)override;
    void updateView(Game &m_gam) override;
    void draw(sf::RenderWindow &win)override;
    void buttons();
    void button_overlay(const sf::RenderWindow &m_win);

    void newMatch(Game &m_gam);

    void titleColor();
    void dibujado(sf::RenderWindow &m_win);
private:
    sf::Font m_font1,m_font2;
    sf::Text m_text1,m_text2,m_text3;
    sf::Texture boton,botonselec;
    sf::Clock timer;
    unsigned char r,g,b;
    sf::RectangleShape shape;
    sf::Vector2i mouse_pos;
    float posx1,posx2,posy1,posy2;
    bool ispressed = false;
};

#endif