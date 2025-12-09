#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/View.hpp>

class player{
public:
    player();
    void update();
    void draw(sf::RenderWindow& m_win);
    void m_mouse();
    void m_key();
    void viewCentre(sf::RenderWindow &m_win);
private:
    sf::Texture m_txt;
    sf::Sprite m_spr;
    sf::View m_view;
    sf::Vector2f pl_pos;
};

#endif