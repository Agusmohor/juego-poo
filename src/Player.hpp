#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/View.hpp>
#include "Entity.hpp"

class player : public entity{
public:
    player();
    void update() override;
    void draw(sf::RenderWindow& m_win) override;
    void m_mouse();
    void m_key();
    void viewCentre(sf::RenderWindow &m_win);
    void speed();
    bool cond();
private:
    sf::View m_view;
    sf::Vector2f pl_pos;
    int stamina;
    sf::Texture m_txt;
    sf::Sprite m_spr;
    float m_speed;
    sf::Vector2f dir;
};

#endif